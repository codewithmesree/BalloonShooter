import React, { useEffect } from 'react';
import { useGameLogic } from '../hooks/useGameLogic';
import Board from './Board';
import UI from './UI';

const Game = () => {
    const {
        gameState,
        mode,
        score,
        balloonsShot,
        totalBalloons,
        arrowsUsed,
        arrowLimit,
        balloons,
        arrows,
        bowX,
        startGame,
        moveBow,
        shootArrow,
        WIDTH,
        HEIGHT
    } = useGameLogic();

    useEffect(() => {
        const handleKeyDown = (e) => {
            if (gameState !== 'PLAYING') return;

            switch (e.key) {
                case 'a':
                case 'A':
                case 'ArrowLeft':
                    moveBow('LEFT');
                    break;
                case 'd':
                case 'D':
                case 'ArrowRight':
                    moveBow('RIGHT');
                    break;
                case ' ':
                    shootArrow();
                    break;
                default:
                    break;
            }
        };

        window.addEventListener('keydown', handleKeyDown);
        return () => window.removeEventListener('keydown', handleKeyDown);
    }, [gameState, moveBow, shootArrow]);

    const hasWon = balloonsShot >= totalBalloons;

    return (
        <div className="game-container">
            <UI
                gameState={gameState}
                mode={mode}
                score={score}
                balloonsShot={balloonsShot}
                totalBalloons={totalBalloons}
                arrowsUsed={arrowsUsed}
                arrowLimit={arrowLimit}
                onStart={startGame}
                hasWon={hasWon}
            />

            <Board
                width={WIDTH}
                height={HEIGHT}
                balloons={balloons}
                arrows={arrows}
                bowX={bowX}
            />

            <div className="controls-hint">
                <p>Controls: A/D or Left/Right to Move | SPACE to Shoot</p>
            </div>
        </div>
    );
};

export default Game;
