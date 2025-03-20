import React from 'react';
import { Link } from 'react-router-dom';

function Header() {
  return (
    <nav>
      <Link to="https://www.unswphoto.com/">
        <img src="/assets/photosoc.png" alt="UNSW Photo" className="logo"/>
      </Link>
      <div className="nav-links">
        <Link to="/">Home</Link>
        <Link to="/upload">Upload</Link>
        <Link to="/voting">Voting</Link>
        <Link to="/photo-of-the-month">Photo of the Month</Link>
      </div>
    </nav>
  );
}

export default Header;