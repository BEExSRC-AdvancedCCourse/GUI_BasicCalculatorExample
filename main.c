#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

typedef enum {
    STATE_MAIN_MENU,
    STATE_BASIC_CALCULATION,
    STATE_GCD,
    STATE_EXIT,
} gui_window_state_t;

gui_window_state_t g_window_state = STATE_MAIN_MENU;

int GUI_DrawButtonBack() {
    Rectangle button_bounds = (Rectangle) { 0, 0, 35, 35 };

    int result = GuiButton(button_bounds, NULL);
    GuiDrawIcon(ICON_ARROW_LEFT_FILL, 1, 1, 2, BLACK);

    return result;
}

void GUI_Init(void) {
    /* Initialize the Window */
    InitWindow(320, 440, "Simple Calculator");
    SetTargetFPS(60);

    /* Set default font size */
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);   
}

void GUI_DrawWindow_MainMenu(void) {
    /* Define button size and position */
    Rectangle title_bound = (Rectangle) { 0, 50, 320, 30 };
    Rectangle mode_basic_calc_bound = (Rectangle) { 20, 100, 280, 80 };
    Rectangle mode_gcd_bound = (Rectangle) { 20, 200, 280, 80 };
    Rectangle mode_exit_bound = (Rectangle) { 20, 300, 280, 80 };

    /* Draw button */
    GuiDrawText("MAIN MENU", title_bound, TEXT_ALIGN_CENTER, BLACK);
    if (GuiButton(mode_basic_calc_bound, "Basic Calculation")) {
        g_window_state = STATE_BASIC_CALCULATION;
    }
    if (GuiButton(mode_gcd_bound, "GCD")) {
        g_window_state = STATE_GCD;
    }
    if (GuiButton(mode_exit_bound, "Exit")) {
        g_window_state = STATE_EXIT;
    }
}

void GUI_DrawWindow_BasicCalculation(void) {
    /* Define variables */
    static int first_number = 0;
    static int second_number = 0;
    static int result = 0;
    static char operator_input[2];
    static bool fn_edit_mode = false;
    static bool sn_edit_mode = false;
    static bool oi_edit_mode = false;

    /* Define controls size and position */
    Rectangle title_bound = (Rectangle) { 0, 50, 320, 30 };
    Rectangle first_number_bound = (Rectangle) { 20, 100, 280, 60 };
    Rectangle second_number_bound = (Rectangle) { 20, 220, 280, 60 };
    Rectangle result_bound = (Rectangle) { 20, 340, 280, 60 };
    Rectangle operator_bound = (Rectangle) { 145, 175, 30, 30 };
    Rectangle equal_sign_bound = (Rectangle) { 0, 295, 320, 30 };

    /* Draw controls */
    if (GUI_DrawButtonBack()) {
        g_window_state = STATE_MAIN_MENU;
    }
    GuiDrawText("BASIC CALCULATION", title_bound, TEXT_ALIGN_CENTER, BLACK);
    if (GuiValueBox(first_number_bound, NULL, &first_number, 0, INT_MAX, fn_edit_mode)) {
        fn_edit_mode = !fn_edit_mode;
    }
    if (GuiValueBox(second_number_bound, NULL, &second_number, 0, INT_MAX, sn_edit_mode)) {
        sn_edit_mode = !sn_edit_mode;
    };
    GuiValueBox(result_bound, NULL, &result, 0, INT_MAX, false);
    if (GuiTextBox(operator_bound, operator_input, 2, oi_edit_mode)) {
        oi_edit_mode = !oi_edit_mode;
        
        char operator = operator_input[0];
        if (!(operator == '+' || operator == '-' || operator == '*' || operator == '/')) {
            operator_input[0] = '+';
        }
    }

    char operator = operator_input[0];
    if (operator == '+') result = first_number + second_number;
    else if (operator == '-') result = first_number - second_number;
    else if (operator == '*') result = first_number * second_number;
    else if (operator == '/') {
        if (second_number == 0) result = 0;
        else result = first_number / second_number;
    }
    GuiDrawText("=", equal_sign_bound, TEXT_ALIGN_CENTER, BLACK);
}

int main()
{
    /* 0. Initialize Program */
    GUI_Init();

    while (!WindowShouldClose())
    {
        /* 1. Event Handling */

        /* 2. Update GUI Parameter */

        /* 3. Drawing GUI */
        BeginDrawing();
        ClearBackground(WHITE);

        if (g_window_state == STATE_MAIN_MENU) {
            GUI_DrawWindow_MainMenu();
        }
        else if (g_window_state == STATE_BASIC_CALCULATION) {
            GUI_DrawWindow_BasicCalculation();
        }
        else if (g_window_state == STATE_GCD) {

        }
        else if (g_window_state == STATE_EXIT) {
            EndDrawing();
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}