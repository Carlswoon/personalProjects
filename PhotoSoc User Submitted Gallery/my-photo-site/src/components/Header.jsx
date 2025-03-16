import React from 'react';
import { Link } from 'react-router-dom';

function Header() {
  return (
    <nav>
      <Link to="/">Home</Link>
      <Link to="/upload">Upload</Link>
      <Link to="/voting">Voting</Link>
      <Link to="/photo-of-the-month">Photo of the Month</Link>
    </nav>
  );
}

export default Header;
