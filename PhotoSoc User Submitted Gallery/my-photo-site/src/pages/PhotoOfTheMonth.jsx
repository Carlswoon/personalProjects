import React from 'react';

function PhotoOfTheMonth({ photo }) {
  if (!photo) {
    return <div>No votes yet for Photo of the Month!</div>;
  }

  return (
    <div>
      <h1>Photo of the Month</h1>
      <img
        src={photo.src}
        alt={photo.title}
        style={{ width: '300px', borderRadius: '8px' }}
      />
      <div className="title">{photo.title}</div>
      <div className="author">By {photo.author}</div>
      <p>Votes: {photo.votes}</p>
    </div>
  );
}

export default PhotoOfTheMonth;