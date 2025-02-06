% Load data from file
data = load('springmass.txt');

% Each line contains: x1 y1 x2 y2 spring_length
% Extract positions for mass1 and mass2
mass1_x = data(:,1);  % First x coordinate
mass1_y = data(:,2);  % First y coordinate
mass2_x = data(:,3);  % Second x coordinate
mass2_y = data(:,4);  % Second y coordinate
spring_lengths = data(:,5);  % Spring lengths (after $ symbol)

% Create animation
figure;
hold on;
axis([-1 1 -1 1]);  % Same bounds as simulation
grid on;

for i = 1:length(mass1_x)
    % Clear previous frame
    clf;
    hold on;
    axis([-1 1 -1 1]);
    grid on;
    
    % Plot masses as points
    plot(mass1_x(i), mass1_y(i), 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
    plot(mass2_x(i), mass2_y(i), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
    
    % Plot spring as line
    line([mass1_x(i) mass2_x(i)], [mass1_y(i) mass2_y(i)], 'Color', 'k');
    
    % Add title with spring length
    title(['Spring Length: ' num2str(spring_lengths(i))]);
    
    % Force MATLAB to draw now
    drawnow;
    pause(0.03);  % 30 fps
end 