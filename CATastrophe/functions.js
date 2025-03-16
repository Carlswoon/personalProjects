
import { config } from './constants.js';

export function generateGrid(gameMap, gridSize, tiles) {
    for (let i = 0; i < config.totalTiles; i++) {
      const tile = document.createElement('div');
      tile.classList.add('tile');
      tiles.push(tile);
      gameMap.appendChild(tile);
    }
}

export function spawnCat(tiles, player) {
  const catPosition = Math.floor(Math.random() * config.totalTiles); // Random tile
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