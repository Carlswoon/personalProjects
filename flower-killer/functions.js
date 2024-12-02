const frameSize = 64;
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
  cat.style.backgroundSize = 'cover';
  cat.style.width = `${frameSize}px`;
  cat.style.height = `${frameSize}px`;

  // Ensure the cat does not spawn where the player is
  if (tiles[catPosition].contains(player)) {
    spawnCat(tiles, player); // Retry if the position overlaps with the player
  } else {
    tiles[catPosition].appendChild(cat); // Add cat to a random tile
  }
}
