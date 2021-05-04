//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_app.h"

namespace connect4 {
    Connect4App::Connect4App() {
        ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
        current_col_ = board_.GetLength() / 2;
        showing_menu_ = true;
    }

    void Connect4App::draw() {
        ci::Color background_color("white");
        ci::gl::clear(background_color);
        if (!showing_menu_) {
            drawBoard();
            if (board_.IsPlayerOneTurn()) {
                ci::gl::color(ci::Color("red"));
            } else {
                ci::gl::color(ci::Color("yellow"));
            }
            ci::gl::drawSolidTriangle(
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace() + (board_.GetXSpace() / 2)),
                              (kWindowSizeY / 4) - 5),
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace()) - (board_.GetXSpace() / 2) +
                              (board_.GetXSpace() / 2),
                              (kWindowSizeY / 4) - board_.GetYSpace()),
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace()) + (board_.GetXSpace() / 2) +
                              (board_.GetXSpace() / 2),
                              (kWindowSizeY / 4) - board_.GetYSpace()));

            ci::gl::color(ci::Color("red"));
            ci::gl::drawSolidRect(ci::Rectf(glm::vec2(0, 0), glm::vec2(kWindowSizeX / 4, kWindowSizeY)));
            ci::gl::color(ci::Color("yellow"));
            ci::gl::drawSolidRect(ci::Rectf(glm::vec2(3 * (kWindowSizeX / 4), 0), glm::vec2(kWindowSizeX, kWindowSizeY)));
            ci::gl::drawStringCentered("Player One", glm::vec2(kWindowSizeX / 8, kWindowSizeY / 8),ci::Color("black"), med);
            ci::gl::drawStringCentered("Player Two", glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 8),ci::Color("black"), med);

            ci::gl::color(ci::Color("black"));
            if (board_.IsPlayerOneTurn()) {
                ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(2,2), glm::vec2(kWindowSizeX / 4, kWindowSizeY / 4)), 4);
            } else {
                ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(3 * (kWindowSizeX / 4),2), glm::vec2(kWindowSizeX - 2, (kWindowSizeY / 4))), 4);
            }
        } else {
            drawMenu();
        }
    }

    void Connect4App::update() {
    }

    void Connect4App::drawBoard() {
        try {
            board_.DrawBoard();
        } catch (std::exception &e) {
            std::cout << e.what();
        }
    }

    void Connect4App::initializeBoard() {
        board_ = GameBoard(length_, height_, win_length_, true, 0, kWindowSizeX, 0, kWindowSizeY);

    }

    void Connect4App::drawMenu() const {
        ci::Color background_color("white");
        ci::gl::clear(background_color);


        ci::gl::drawStringCentered("Press 1 for a Standard Game", glm::vec2(kWindowSizeX / 2, kWindowSizeY / 8),
                                   ci::Color("black"), large);
        ci::gl::drawStringCentered("Press 2 for a Wild Game", glm::vec2(kWindowSizeX / 2, 2 * (kWindowSizeY / 8)),
                                   ci::Color("black"), large);
        ci::gl::drawStringCentered("Use the left and right arrow to change the length of the board",
                                   glm::vec2(kWindowSizeX / 2, 3 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);
        ci::gl::drawStringCentered("Use the up and down arrows to change the height of the board",
                                   glm::vec2(kWindowSizeX / 2, 4 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);
        ci::gl::drawStringCentered("Use '<' and '>' to change the win length",
                                   glm::vec2(kWindowSizeX / 2, 5 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);

        ci::gl::drawStringCentered("Height: " + std::to_string(height_),
                                   glm::vec2(kWindowSizeX / 2, 11 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
        ci::gl::drawStringCentered("Length: " + std::to_string(length_),
                                   glm::vec2(kWindowSizeX / 2, 12 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
        ci::gl::drawStringCentered("Win Length: " + std::to_string(win_length_),
                                   glm::vec2(kWindowSizeX / 2, 13 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
    }

    void Connect4App::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_RIGHT:
                if (!showing_menu_) {
                    if (current_col_ + 1 < board_.GetLength()) {
                        current_col_++;
                    }
                } else {
                    length_++;
                }
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                if (!showing_menu_) {
                    if (current_col_ - 1 >= 0) {
                        current_col_--;
                    }
                } else {
                    if (length_ - 1 >= 0) {
                        length_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_UP:
                if (showing_menu_) {
                    height_++;
                }
                break;

            case ci::app::KeyEvent::KEY_DOWN:
                if (showing_menu_) {
                    if (height_ - 1 >= 0) {
                        height_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_COMMA:
                if (showing_menu_) {
                    if (win_length_ - 1 >= 0) {
                        win_length_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_PERIOD:
                if (showing_menu_) {
                    win_length_++;
                }
                break;


            case ci::app::KeyEvent::KEY_RETURN:
                try {
                    board_.DropPiece(current_col_, false);
                } catch (const std::exception &e) {
                    std::cout << "Error!" << std::endl;
                }
                break;

            case ci::app::KeyEvent::KEY_ESCAPE:
                if (!showing_menu_) {
                    showing_menu_ = true;
                    board_.Clear();
                    current_col_ = board_.GetLength() / 2;
                }
                break;

            case ci::app::KeyEvent::KEY_1:
                if (showing_menu_) {
                    showing_menu_ = false;
                    game_type_ = 1;
                    initializeBoard();
                }

            case ci::app::KeyEvent::KEY_2:
                if (showing_menu_) {
                    showing_menu_ = false;
                    game_type_ = 2;
                    initializeBoard();
                }
        }
    }


}
