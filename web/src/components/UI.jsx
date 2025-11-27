import React from 'react';

const UI = ({
    gameState,
    mode,
    score,
    balloonsShot,
    totalBalloons,
    arrowsUsed,
    arrowLimit,
    onStart,
    hasWon
}) => {
    if (gameState === 'MENU') {
        return (
            <div className="ui-overlay">
                <h1>Balloon Shooter</h1>
                <button className="menu-button" onClick={() => onStart('EASY')}>
                    Easy Mode (Unlimited Arrows)
                </button>
                <button className="menu-button" onClick={() => onStart('HARD')}>
                    Hard Mode (Limited Arrows)
                </button>
            </div>
        );
    }

    if (gameState === 'GAME_OVER') {
        return (
            <div className="ui-overlay">
                <h1>GAME OVER</h1>
                <h2>{hasWon ? 'YOU WIN! 🎉' : 'YOU LOSE! 💀'}</h2>
                <p>Final Score: {score}</p>
                <button className="menu-button" onClick={() => window.location.reload()}>
                    Play Again
                </button>
            </div>
        );
    }

    return (
        <div className="stats-bar">
            <div>Score: {score}</div>
            <div>Balloons: {balloonsShot}/{totalBalloons}</div>
            <div>
                Arrows: {arrowsUsed}
                {mode === 'HARD' && `/${arrowLimit}`}
            </div>
        </div>
    );
};

export default UI;
