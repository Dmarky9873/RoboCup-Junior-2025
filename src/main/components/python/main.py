import pygame
import math

pygame.init()

WIDTH, HEIGHT = 600, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

center = (300, 300)  
radius = 100         
num_circles = 16    
circle_radius = 10

brightness_values = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4] #test values

running = True
while running:
    screen.fill("white") 
    pygame.draw.circle(screen, "black", (300, 300), 100)
    for i in range(num_circles):
        angle = (i / num_circles) * 2 * math.pi  # Calculate angle
        x = int(center[0] + radius * math.cos(angle))
        y = int(center[1] + radius * math.sin(angle))

        # Scale brightness (0-1) to red intensity (0-255)
        red_intensity = int(brightness_values[i] * 255)
        color = (red_intensity, 0, 0)  # RGB, only red varies

        pygame.draw.circle(screen, color, (x, y), circle_radius)

    pygame.display.flip() 

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    clock.tick(60) 

pygame.quit()
