#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define WIDTH 11
#define HEIGHT 5
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 사각형의 좌표를 출력하는 함수
void printSquare(float square[4][2], float angle) {
    // 화면을 비우기
    system("cls");

    // 화면 초기화
    char screen[25][80];
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            screen[i][j] = ' '; // 화면 초기화
        }
    }

    // 사각형의 꼭짓점과 내부 채우기
    for (int i = 0; i < 4; i++) {
        // 현재 꼭짓점 좌표 계산
        int x = (int)(square[i][0] + CENTER_X + (80 / 2));
        int y = (int)(square[i][1] + CENTER_Y + (25 / 2));
        if (x >= 0 && x < 80 && y >= 0 && y < 25) {
            screen[y][x] = '.'; // 꼭짓점 표시
        }
    }

    // 사각형 내부 채우기
    for (int y = -CENTER_Y; y <= CENTER_Y; y++) {
        for (int x = -CENTER_X; x <= CENTER_X; x++) {
            // 회전된 좌표 계산
            float rotatedX = x * cos(angle * M_PI / 180.0) - y * sin(angle * M_PI / 180.0);
            float rotatedY = x * sin(angle * M_PI / 180.0) + y * cos(angle * M_PI / 180.0);

            // 사각형의 경계 내에 있는지 확인
            if (fabs(rotatedX) <= 5.5 && fabs(rotatedY) <= 2.5) {
                int screenX = (int)(rotatedX + CENTER_X + (80 / 2));
                int screenY = (int)(rotatedY + CENTER_Y + (25 / 2));
                if (screenX >= 0 && screenX < 80 && screenY >= 0 && screenY < 25) {
                    screen[screenY][screenX] = '.'; // 내부를 '.'으로 채움
                }
            }
        }
    }

    // 화면 출력
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

// 중심을 기준으로 회전 함수
void rotateSquare(float square[4][2], float angle) {
    float rad = angle * M_PI / 180.0; // 각도를 라디안으로 변환
    float cosA = cos(rad);
    float sinA = sin(rad);

    for (int i = 0; i < 4; i++) {
        // 현재 점 좌표
        float x = square[i][0];
        float y = square[i][1];

        // 회전
        square[i][0] = x * cosA - y * sinA; // 새로운 x
        square[i][1] = x * sinA + y * cosA; // 새로운 y
    }
}

int main() {
    // 사각형의 4점 좌표 초기화 (중심을 기준으로)
    float square[4][2] = {
        {-5.5, -2.5}, // 왼쪽 아래
        {5.5, -2.5},  // 오른쪽 아래
        {5.5, 2.5},   // 오른쪽 위
        {-5.5, 2.5}   // 왼쪽 위
    };

    // 3초에 한 바퀴 (360도) 회전
    const int frames = 30; // 30 프레임
    const float anglePerFrame = 360.0 / frames; // 프레임당 회전 각도

    // 애니메이션 루프
    while (1) {
        for (int i = 0; i < frames; i++) {
            printSquare(square, i * anglePerFrame);  // 현재 상태 출력
            rotateSquare(square, anglePerFrame);  // 사각형 회전
            Sleep(100); // 0.1초 대기
        }
    }

    return 0;
}

