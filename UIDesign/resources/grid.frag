// grid_shader.frag
uniform float gridSize;      // Size of each grid cell
uniform float lineWidth;     // Thickness of the grid lines
uniform vec3 gridColor;      // RGB color for the grid lines
uniform vec3 backgroundColor; // RGB color for the background

uniform vec2 viewCenter;     // Center of the current view
uniform vec2 viewSize;       // Size of the view (width, height)

void main() {
    // Get the fragment's world position
    vec2 fragCoord = (gl_FragCoord.xy / viewSize) * 2.0 - 1.0; 
    vec2 worldPos = fragCoord * (viewSize * 0.5) + viewCenter;

    // Calculate grid lines based on the world position
    float xLine = mod(worldPos.x, gridSize);
    float yLine = mod(worldPos.y, gridSize);

    // Determine if the fragment is near a line
    float lineX = step(gridSize - lineWidth, xLine) + step(xLine, lineWidth);
    float lineY = step(gridSize - lineWidth, yLine) + step(yLine, lineWidth);

    // Mix grid and background color
    vec3 color = mix(backgroundColor, gridColor, max(lineX, lineY));
    
    // Output the final color
    gl_FragColor = vec4(color, 1.0);
}