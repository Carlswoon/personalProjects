
const gridSize = 10;
const totalTiles = gridSize * gridSize;

export function generateGrid(gridSize, gameMap, tiles) {
    for (let i = 0; i < gridSize * gridSize; i++) {
      const tile = document.createElement('div');
      tile.classList.add('tile');
      tiles.push(tile);
      gameMap.appendChild(tile);
    }
  }

export function spawnCat(tiles, player) {
  const catPosition = Math.floor(Math.random() * totalTiles); // Random tile
  const cat = document.createElement('img'); 
  cat.src = './assets/images/cat-sleep.gif'; // Path to the cat GIF  cat.alt = 'Cat';
  cat.classList.add('cat');

  // Ensure the cat does not spawn where the player is
  if (tiles[catPosition].contains(player)) {
    spawnCat(tiles, player); // Retry if the position overlaps with the player
  } else {
    tiles[catPosition].appendChild(cat); // Add cat to a random tile
  }
}

// playerMovement.js

// playerMovement.js
// playerMovement.js
export function movePlayer(event, gameState) {
  const { directions, gridSize, tiles, player, frameSize, framesPerRow } = gameState;
  const { playerPosition, setPlayerPosition, animationFrame, setAnimationFrame } = gameState;

  const key = event.key.toLowerCase();
  if (!directions[key]) return; // Ignore keys other than WASD

  const { dx, dy, row } = directions[key];
  const newX = (playerPosition % gridSize) + dx;
  const newY = Math.floor(playerPosition / gridSize) + dy;

  // Prevent movement out of bounds
  if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) return;

  // Calculate new position
  const newPosition = newY * gridSize + newX;

  // Move the player element to the new tile
  tiles[playerPosition].removeChild(player); // Remove player from the current tile
  tiles[newPosition].appendChild(player); // Attach player to the new tile

  // Update player position
  setPlayerPosition(newPosition);

  // Update animation frame and direction
  const newAnimationFrame = (animationFrame + 1) % framesPerRow;
  setAnimationFrame(newAnimationFrame);

  // Update the sprite's background position
  const xOffset = newAnimationFrame * frameSize; // Horizontal position (frame)
  const yOffset = row * frameSize; // Vertical position (row for direction)
  player.style.backgroundPosition = `-${xOffset}px -${yOffset}px`;
}


