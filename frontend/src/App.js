import React, { useState, useEffect } from 'react';
import './App.css';

function App() {
  const [command, setCommand] = useState('');
  const [history, setHistory] = useState([]);

  useEffect(() => {
    const handleKeyDown = (event) => {
      if (event.key === 'Enter') {
        // Process the command here
        setHistory([...history, `user@localhost:~/$ ${command}`]);
        setCommand('');
      } else if (event.key === 'Backspace') {
        setCommand(command.slice(0, -1));
      } else if (event.key.length === 1) {
        setCommand(command + event.key);
      }
    };

    window.addEventListener('keydown', handleKeyDown);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, [command, history]);

  return (
    <div className="App">
      <header className="App-header">
        <div className="fakeMenu">
          {/* ... */}
        </div>
        <div className="fakeScreen">
          {history.map((line, index) => (
            <p key={index}>{line}</p>
          ))}
          <p>
            {`user@localhost:~/$ ${command}`}
            <span className="active-cursor">_</span> {/* Updated class name */}
          </p>
        </div>
      </header>
    </div>
  );
}

export default App;