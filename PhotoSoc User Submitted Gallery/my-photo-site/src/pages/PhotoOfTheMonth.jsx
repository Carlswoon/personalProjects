import React from 'react';
import { useState } from 'react';

function PhotoOfTheMonth() {
  const [votes, setVotes] = useState(0);

  const handleVote = () => {
    setVotes(votes + 1);
  };

  return (
    <div>
      <h1>Photo of the Month</h1>
      <img src="/assets/photo-of-the-month.png" alt="Photo of the Month" style={{ width: '300px', borderRadius: '8px' }} />
      <div className="title">A Foggy Morning</div>
      <div className="author">Freeman Xu</div>
      <p>Votes: {votes}</p>
      <button onClick={handleVote}>Vote</button>
    </div>
  );
}

export default PhotoOfTheMonth;
