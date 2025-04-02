import math
import pygame
from reading_serial_monitor import readserial


# pylint: disable=no-member
pygame.init()

WIDTH, HEIGHT = 600, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

center = (300, 300)
radius = 100
num_circles = 16
circle_radius = 10

brightness_values = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
                     0.9, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4]  # test values

running = True
while running:

    brightness_values = []

    raw = readserial('/dev/tty.usbmodem139169701', 9600)

    raw = raw[1:len(raw) - 1].split(' ')

    for i, value in enumerate(raw):
        if value != '':
            try:
                # Uncomment for floating point ranged values
                brightness_values.append(float(value))

                # Uncomment for rounded, on/off binary
                brightness_values.append(round(float(value)))
            except ValueError as e:
                # Uncomment for floating point ranged values
                brightness_values.append(float(value[:len(value) - 2]))

                # Uncomment for rounded, on/off binary
                # brightness_values.append(round(float(value[:len(value) - 2])))

    print(brightness_values)

    screen.fill("white")
    pygame.draw.circle(screen, "black", (300, 300), 100)
    for i in range(num_circles):
        angle = (i / num_circles) * 2 * math.pi  # Calculate angle
        x = int(center[0] + radius * math.cos(angle))
        y = int(center[1] + radius * math.sin(angle))

        # Scale brightness (0-1) to red intensity (0-255)
        if i > len(brightness_values) - 1:
            red_intensity = 0
        else:
            red_intensity = int(brightness_values[i] * 255)
        color = (red_intensity, 0, 0)  # RGB, only red varies

        try:
            pygame.draw.circle(screen, color, (x, y), circle_radius)
        except ValueError as e:
            print(e)
            print(color)

    pygame.display.flip()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    clock.tick(60)

pygame.quit()
