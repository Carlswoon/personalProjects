import { generateGrid, spawnCat } from './functions.js';

const gameMap = document.getElementById('gameMap');

// Sprite sheet details
const playerImgSrc = './assets/images/player.png'; // Path to the player sprite sheet
const frameSize = 64; // Size of each frame (assumed 64x64px)
const framesPerRow = 3; // Number of frames in each row

// Directions and corresponding sprite rows
const directions = {
  w: { dx: 0, dy: -1, row: 3 }, // Up
  a: { dx: -1, dy: 0, row: 1 }, // Left
  s: { dx: 0, dy: 1, row: 0 }, // Down
  d: { dx: 1, dy: 0, row: 2 }, // Right
};

// Generate a 10x10 grid
const gridSize = 10;
const totalTiles = gridSize * gridSize;
const tiles = [];

generateGrid(gridSize, gameMap, tiles);

// Place the player at the center of the grid
let playerPosition = Math.floor(totalTiles / 2); // Start position in the center
const player = document.createElement('div'); // Create the player element
player.classList.add('player');
player.style.backgroundImage = `url(${playerImgSrc})`;
player.style.backgroundSize = `${frameSize * framesPerRow}px ${frameSize * 4}px`; // Adjust to sprite sheet size
player.style.width = `${frameSize}px`;
player.style.height = `${frameSize}px`;
player.style.backgroundRepeat = 'no-repeat';
player.style.backgroundPosition = `0px 0px`;
tiles[playerPosition].appendChild(player); // Attach the player to the initial tile

spawnCat(tiles, player);

// Current animation state
let currentDirection = 's'; // Default direction is down
let animationFrame = 0;

// Function to move the player
function movePlayer(event) {
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
  playerPosition = newPosition;

  // Update animation frame and direction
  animationFrame = (animationFrame + 1) % framesPerRow; // Cycle through 3 frames
  currentDirection = key;

  // Update the sprite's background position
  const xOffset = animationFrame * frameSize; // Horizontal position (frame)
  const yOffset = row * frameSize; // Vertical position (row for direction)
  player.style.backgroundPosition = `-${xOffset}px -${yOffset}px`;
}

// Listen for keyboard events
document.addEventListener('keydown', movePlayer);
