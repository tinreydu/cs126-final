//
// Created by tinre on 4/19/2021.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "connect4_board.h"

namespace connect4 {
    class Connect4App : public ci::app::App {
    public:
        Connect4App();

        void draw() override;

        void update() override;

        void keyDown(ci::app::KeyEvent event) override;

        const int kWindowSizeX = 1920;
        const int kWindowSizeY = 1080;
        const int kMargin = 100;

    private:
        size_t current_col_;
        size_t last_piece_col_;
        size_t last_piece_row_;
        bool started_;

        GameBoard board_ = GameBoard(7, 6, 4, true, 0, kWindowSizeX, 0, kWindowSizeY);
    };
}


