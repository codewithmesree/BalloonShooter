import React from 'react';

const Board = ({ width, height, balloons, arrows, bowX }) => {
    // We can render entities absolutely positioned on top of the board
    // The board itself can be a simple container with dimensions

    // Calculate percentage positions for responsiveness
    const getStyle = (x, y) => ({
        left: `${(x / width) * 100}%`,
        top: `${(y / height) * 100}%`,
        width: `${(1 / width) * 100}%`,
        height: `${(1 / height) * 100}%`,
    });

    return (
        <div
            className="game-board"
            style={{
                width: '800px',
                height: '400px',
                position: 'relative'
            }}
        >
            {/* Balloons */}
            {balloons.map(b => (
                <div
                    key={b.id}
                    className="entity balloon"
                    style={getStyle(b.x, b.y)}
                >
                    🎈
                </div>
            ))}

            {/* Arrows */}
            {arrows.map(a => (
                <div
                    key={a.id}
                    className="entity arrow"
                    style={getStyle(a.x, a.y)}
                >
                    ⬆️
                </div>
            ))}

            {/* Bow */}
            <div
                className="entity bow"
                style={getStyle(bowX, height - 2)}
            >
                🏹
            </div>
        </div>
    );
};

export default Board;
