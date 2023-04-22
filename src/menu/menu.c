#include "menu.h"

#include "../util/memory.h"

Gfx* menuBuildText(struct Font* font, char* message, int x, int y) {
    Gfx* result = malloc(sizeof(Gfx) * (fontCountGfx(font, message) + 1));
    Gfx* dl = result;

    dl = fontRender(font, message, x, y, dl);
    gSPEndDisplayList(dl++);

    return result;
}

Gfx* menuBuildBorder(int x, int y, int width, int height) {
    Gfx* result = malloc(sizeof(Gfx) * 7 * 3 + 1);
    Gfx* dl = result;

    gSPTextureRectangle(
        dl++,
        x << 2, y << 2,
        (x + 4) << 2, (y + 4) << 2,
        G_TX_RENDERTILE,
        0 << 5, 0 << 5,
        0x400, 0x400
    );

    gSPTextureRectangle(
        dl++,
        (x + 4) << 2, y << 2,
        (x + width - 4) << 2, (y + 4) << 2,
        G_TX_RENDERTILE,
        4 << 5, 4 << 5,
        0, 0
    );

    gSPTextureRectangle(
        dl++,
        (x + width - 4) << 2, y << 2,
        (x + width) << 2, (y + 4) << 2,
        G_TX_RENDERTILE,
        4 << 5, 0 << 5,
        0x400, 0x400
    );

    gSPTextureRectangle(
        dl++,
        x << 2, (y + 4) << 2,
        (x + width) << 2, (y + height - 4) << 2,
        G_TX_RENDERTILE,
        4 << 5, 4 << 5,
        0, 0
    );

    gSPTextureRectangle(
        dl++,
        x << 2, (y + height - 4) << 2,
        (x + 4) << 2, (y + height) << 2,
        G_TX_RENDERTILE,
        0 << 5, 4 << 5,
        0x400, 0x400
    );

    gSPTextureRectangle(
        dl++,
        (x + 4) << 2, (y + height - 4) << 2,
        (x + width - 4) << 2, (y + height) << 2,
        G_TX_RENDERTILE,
        4 << 5, 4 << 5,
        0, 0
    );

    gSPTextureRectangle(
        dl++,
        (x + width - 4) << 2, (y + height - 4) << 2,
        (x + width) << 2, (y + height) << 2,
        G_TX_RENDERTILE,
        4 << 5, 4 << 5,
        0x400, 0x400
    );

    gSPEndDisplayList(dl++);

    return result;
}

Gfx* menuBuildHorizontalLine(int x, int y, int width) {
    Gfx* result = malloc(sizeof(Gfx) * 7);

    Gfx* dl = result;
    gDPPipeSync(dl++);
    gDPSetEnvColor(dl++, 86, 86, 86, 128);
    gDPFillRectangle(dl++, x, y, x + width, y + 1);
    gDPPipeSync(dl++);
    gDPSetEnvColor(dl++, 193, 193, 193, 128);
    gDPFillRectangle(dl++, x, y + 1, x + width, y + 2);
    gSPEndDisplayList(dl++);

    return result;
}

Gfx* menuBuildSolidBorder(int x, int y, int w, int h, int nx, int ny, int nw, int nh) {
    Gfx* result = malloc(sizeof(Gfx) * 5);
    Gfx* dl = result;

    gDPFillRectangle(dl++, x, y, x + w, ny);
    gDPFillRectangle(dl++, x, ny, nx, ny + nh);
    gDPFillRectangle(dl++, nx + nw, ny, x + w, ny + nh);
    gDPFillRectangle(dl++, x, ny + nh, x + w, y + h);
    gSPEndDisplayList(dl++);

    return result;
}

struct MenuButton menuBuildButton(struct Font* font, char* message, int x, int y, int width, int height) {
    struct MenuButton result;

    result.text = menuBuildText(font, message, x + 4, y + 2);
    result.outline = malloc(sizeof(Gfx) * 9);

    Gfx* dl = result.outline;

    gDPPipeSync(dl++);
    gDPSetEnvColor(dl++, 188, 188, 188, 255);
    gDPFillRectangle(dl++, x, y, x + width - 1, y + 1);
    gDPFillRectangle(dl++, x, y, x + 1, y + height);
    gDPPipeSync(dl++);
    gDPSetEnvColor(dl++, 76, 76, 76, 255);
    gDPFillRectangle(dl++, x, y + height - 1, x + width, y + height);
    gDPFillRectangle(dl++, x + width - 1, y, x + width, y + height - 1);
    gSPEndDisplayList(dl++);

    return result;
}