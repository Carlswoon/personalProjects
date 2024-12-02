import { generateGrid, spawnCat } from './functions.js';
import { movePlayer, createPlayer } from './playerFunction.js';
import { config } from './constants.js';

// Game initialization
function initializeGame(config) {
  const gameMap = document.getElementById('gameMap');
  const tiles = [];
  const totalTiles = config.gridSize * config.gridSize;

  // Generate the game grid
  generateGrid(gameMap, config.gridSize, tiles);

  // Create the player and place it at the center
  const player = createPlayer(config.playerImgSrc, config.frameSize, config.framesPerRow);
  let playerPosition = Math.floor(totalTiles / 2);
  tiles[playerPosition].appendChild(player);

  // Spawn the cat
  spawnCat(tiles, player);

  // Game state object
  const gameState = {
    gridSize: config.gridSize,
    tiles,
    player,
    playerPosition,
    currentDirection: 's',
    animationFrame: 0,
    directions: config.directions,
    frameSize: config.frameSize,
    framesPerRow: config.framesPerRow,
  };

  // Attach keyboard event listener
  document.addEventListener('keydown', (event) => movePlayer(event, gameState));
}

// Initialize the game
initializeGame(config);