export function createPlayer(imgSrc, frameSize, framesPerRow) {
    const player = document.createElement('div');
    player.classList.add('player');
    player.style.backgroundImage = `url(${imgSrc})`;
    player.style.backgroundSize = `${frameSize * framesPerRow}px auto`;
    return player;
}

export function movePlayer(event, gameState) {
    const key = event.key.toLowerCase();
    if (!gameState.directions[key]) return; // Ignore keys other than WASD
  
    const { dx, dy, row } = gameState.directions[key];
    const newX = (gameState.playerPosition % gameState.gridSize) + dx;
    const newY = Math.floor(gameState.playerPosition / gameState.gridSize) + dy;
  
    // Prevent movement out of bounds
    if (newX < 0 || newX >= gameState.gridSize || newY < 0 || newY >= gameState.gridSize) return;
  
    // Calculate new position
    const newPosition = newY * gameState.gridSize + newX;
  
    // Move the player element to the new tile
    gameState.tiles[gameState.playerPosition].removeChild(gameState.player); // Remove player from the current tile
    gameState.tiles[newPosition].appendChild(gameState.player); // Attach player to the new tile
  
    // Update player position
    gameState.playerPosition = newPosition;
  
    // Update animation frame and direction
    gameState.animationFrame = (gameState.animationFrame + 1) % gameState.framesPerRow; // Cycle through 3 frames
    gameState.currentDirection = key;
  
    // Update the sprite's background position
    const xOffset = gameState.animationFrame * gameState.frameSize; // Horizontal position (frame)
    const yOffset = row * gameState.frameSize; // Vertical position (row for direction)
    gameState.player.style.backgroundPosition = `-${xOffset}px -${yOffset}px`;
}
  