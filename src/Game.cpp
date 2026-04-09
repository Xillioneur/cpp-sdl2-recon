#include "Game.hpp"
#include <iostream>
#include <queue>

Game::Game() {
    TTF_Init();
    win = SDL_CreateWindow("Recon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 18); 
    if (!font) {
        std::cerr << "Failed to load font: assets/OpenSans-Regular.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
        running = false;
        return;
    }
    fontL = TTF_OpenFont("assets/OpenSans-Regular.ttf", 52);
    if (!fontL) {
        std::cerr << "Failed to load large font: assets/OpenSans-Regular.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
        running = false;
        return;
    }
}

Game::~Game() {
    // TODO: Code cleanup method.
    if(font) TTF_CloseFont(font);
    if(fontL) TTF_CloseFont(fontL);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
}

void Game::init() {
    // Todo: Code the cleanup method.
    generateLevel();
    state = GameState::PLAYING;
    p = new Player(findSpace(24, 24));
}


void Game::generateLevel() {
    bool connected = false;
    while (!connected) {
        map.assign(MAP_HEIGHT, std::vector<Tile>(MAP_WIDTH));
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                map[y][x].type == WALL;
                map[y][x].rect = {(float)x * TILE_SIZE, (float)y * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE};
            }
        }
        std::vector<Rect> rooms;
        for (int i = 0; i < 15; ++i) {
            int w = 6 + rand() % 6, h = 6 + rand() % 6, x = 1 + rand() % (MAP_WIDTH - w - 1), y = 1 + rand() % (MAP_HEIGHT - h - 1);
            Rect r {(float)x, (float)y, (float)w, (float)h};
            bool ok = true;
            for (const auto& ex : rooms) if (r.intersects({ex.x - 1, ex.y - 1, ex.w + 2, ex.h + 2})) {
                ok = false; 
                break; 
            }
            if (ok) {
                rooms.push_back(r);
                for (int ry = y; ry < y + h; ++ry) for (int rx = (int)x; rx < (int)x + w; ++rx) map[ry][rx].type = FLOOR;
            }
        }
        for (size_t i = 1; i < rooms.size(); ++i) {
            Vec2 p1 = rooms[i - 1].center(), p2 = rooms[i].center();
            int xDir = (p2.x > p1.x) ? 1 : -1; for (int x = (int)p1.x; x != (int)p2.x; x += xDir) map[(int)p1.y][x].type = FLOOR;
            int yDir = (p2.y > p1.y) ? 1 : -1; for (int y = (int)p1.y; y != (int)p2.y; y += yDir) map[y][(int)p2.x].type = FLOOR;
        }
        if (rooms.empty()) continue;
        std::vector<std::vector<bool>> reachable(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));
        std::queue<std::pair<int, int>> q; Vec2 start = rooms[0].center();
        q.push({(int)start.x, (int)start.y}); reachable[(int)start.y][(int)start.x] = true;
        reachable[(int)start.y][(int)start.x] = true;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
            for (int i = 0; i < 4; ++i) {
                int nx = cur.first + dx[i], ny = cur.second + dy[i];
                if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT && map[ny][nx].type == FLOOR && !reachable[ny][nx]) { 
                    reachable[ny][nx] = true;
                    q.push({nx, ny});
                }
            }
        }
        connected = true;
        for (int y = 0; y < MAP_HEIGHT; ++y) for (int x = 0; x < MAP_WIDTH; ++x) if (map[y][x].type == FLOOR && !reachable[y][x]) connected  = false;

        if (connected) {
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    if (map[y][x].type == FLOOR && rand() % 100 < 2) map[y][x].type = HAZARD_TILE;
                }
            }
        }
    }
}

Vec2 Game::findSpace(float w, float h) {
    for (int i = 0; i < 2000; ++i) {
        int x = 1 + rand() % (MAP_WIDTH - 2);
        int y = 1 + rand() % (MAP_HEIGHT - 2);
        if (map[y][x].type == FLOOR) {
            Rect r = {(float)x * TILE_SIZE + 2, (float)y * TILE_SIZE + 2, w, h};
            bool safe = true;
            for (int sy = y - 1; sy <= y + 2; sy++) {
                for (int sx = x - 1; sx <= x + 2; sx++) {
                    if (sx >= 0 && sx < MAP_WIDTH && sy >= 0 && sy < MAP_HEIGHT && map[sy][sx].type == WALL && r.intersects(map[sy][sx].rect)) safe = false;
                }
            }
            if (safe) return {r.x, r.y};
        }
    }
    return {MAP_HEIGHT * TILE_SIZE / 2.0f, MAP_HEIGHT * TILE_SIZE / 2.0f};
}

void Game::handleInput() {
    input.update();
    if (input.isPressed(SDL_SCANCODE_RETURN)) {
        if (state != GameState::PLAYING) {
            // TODO: Play sound.
            init();
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(ren, COL_BG.r, COL_BG.g, COL_BG.b, 255);
    SDL_RenderClear(ren);

    if (state == GameState::MENU) {
        SDL_SetRenderDrawColor(ren, 15, 20, 25, 255);
        for (int i = 0; i < SCREEN_WIDTH; i += 40) SDL_RenderDrawLine(ren, i, 0, i, SCREEN_HEIGHT);
        for (int i = 0; i < SCREEN_HEIGHT; i += 40) SDL_RenderDrawLine(ren, 0, i, SCREEN_WIDTH, i);
        // Intersections
        SDL_SetRenderDrawColor(ren, 30, 40, 50, 255);
        for (int x = 0; x < SCREEN_WIDTH; x += 40) {
            for (int y = 0; y < SCREEN_HEIGHT; y += 40) {
                SDL_Rect dot = { x - 1, y - 1, 3, 3 };
                SDL_RenderFillRect(ren, &dot);
            }
        }
    }

    if (state == GameState::MENU) {
        hud.renderMenu(ren, font, fontL);
    } else if (state == GameState::PLAYING) {
        int sx = std::max(0, (int)(cam.x / TILE_SIZE)), sy = std::max(0, (int)(cam.y / TILE_SIZE)); 
        int ex = std::min(MAP_WIDTH, (int)((cam.x + SCREEN_WIDTH) / TILE_SIZE) + 1), ey = std::min(MAP_HEIGHT, (int)((cam.y + SCREEN_HEIGHT) / TILE_SIZE) + 1);
        for (int y = sy; y < ey; ++y) for (int x = sx; x < ex; ++x) {
            SDL_Rect r = {(int)(x * TILE_SIZE - cam.x), (int)(y * TILE_SIZE - cam.y), TILE_SIZE, TILE_SIZE};
            if (map[y][x].type == WALL) SDL_SetRenderDrawColor(ren, COL_WALL.r, COL_WALL.g, COL_WALL.b, 255);
            else if (map[y][x].type == FLOOR) SDL_SetRenderDrawColor(ren, COL_FLOOR.r, COL_FLOOR.g, COL_FLOOR.b, 255);
            else {
                Uint8 flicker = (Uint8)(100 + std::sin(SDL_GetTicks() * 0.02f) * 50);
                SDL_SetRenderDrawColor(ren, flicker, flicker, 0, 255);
            }
            SDL_RenderFillRect(ren, &r);
            if (map[y][x].type == FLOOR) { 
                SDL_SetRenderDrawColor(ren, 50, 50, 100, 255);
                SDL_RenderDrawRect(ren, &r);
            }
        }
    }

    SDL_RenderPresent(ren);
}

void Game::loop() { 
    while (running) { 
        Uint32 st = SDL_GetTicks(); 
        handleInput();
        render();
        Uint32 t = SDL_GetTicks() - st;
        if (t < FRAME_DELAY) SDL_Delay((Uint32)FRAME_DELAY - t);
    }
}