import pygame
import random
import sys

# Инициализация Pygame
pygame.init()

# Размеры экрана
WIDTH, HEIGHT = 800, 600

# Настройка экрана
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Котик собирает рыбу")

# Цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
ORANGE = (255, 165, 0)

# Переменные кота
cat_width, cat_height = 50, 50
cat_x, cat_y = WIDTH // 2, HEIGHT - cat_height - 10
cat_speed = 7

# Рыбка
fish_width, fish_height = 30, 30
fish_x = random.randint(0, WIDTH - fish_width)
fish_y = 0
fish_speed = 5

# Очки
score = 0
font = pygame.font.Font(None, 36)

# Главный цикл игры
clock = pygame.time.Clock()

while True:
    # Обработка событий
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Управление котом
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and cat_x > 0:
        cat_x -= cat_speed
    if keys[pygame.K_RIGHT] and cat_x < WIDTH - cat_width:
        cat_x += cat_speed

    # Движение рыбки
    fish_y += fish_speed

    # Проверка, поймана ли рыбка
    cat_rect = pygame.Rect(cat_x, cat_y, cat_width, cat_height)
    fish_rect = pygame.Rect(fish_x, fish_y, fish_width, fish_height)
    if cat_rect.colliderect(fish_rect):
        score += 1
        fish_x = random.randint(0, WIDTH - fish_width)
        fish_y = 0

    # Если рыбка упала ниже экрана
    if fish_y > HEIGHT:
        fish_x = random.randint(0, WIDTH - fish_width)
        fish_y = 0

    # Рендеринг экрана
    screen.fill(WHITE)

    # Отрисовка кота
    pygame.draw.rect(screen, BLUE, cat_rect)

    # Отрисовка рыбки
    pygame.draw.rect(screen, ORANGE, fish_rect)

    # Отображение очков
    score_text = font.render(f"Очки: {score}", True, BLACK)
    screen.blit(score_text, (10, 10))

    # Обновление дисплея
    pygame.display.flip()

    # Ограничение FPS
    clock.tick(60)
