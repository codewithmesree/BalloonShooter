import { useState, useEffect, useCallback, useRef } from 'react';

const WIDTH = 40;
const HEIGHT = 20;
const BALLOON_SPAWN_RATE = 10; // Frames

export const useGameLogic = () => {
    const [gameState, setGameState] = useState('MENU'); // MENU, PLAYING, GAME_OVER
    const [mode, setMode] = useState('EASY'); // EASY, HARD
    const [score, setScore] = useState(0);
    const [balloonsShot, setBalloonsShot] = useState(0);
    const [arrowsUsed, setArrowsUsed] = useState(0);
    const [balloons, setBalloons] = useState([]);
    const [arrows, setArrows] = useState([]);
    const [bowX, setBowX] = useState(WIDTH / 2);

    const frameCount = useRef(0);
    const requestRef = useRef();
    const lastTimeRef = useRef();

    const totalBalloons = mode === 'EASY' ? 20 : 10;
    const arrowLimit = 15;

    const startGame = (selectedMode) => {
        setMode(selectedMode);
        setGameState('PLAYING');
        setScore(0);
        setBalloonsShot(0);
        setArrowsUsed(0);
        setBalloons([]);
        setArrows([]);
        setBowX(WIDTH / 2);
        frameCount.current = 0;
    };

    const spawnBalloon = useCallback(() => {
        const spawnX = Math.floor(Math.random() * (WIDTH - 4)) + 2;
        setBalloons(prev => [...prev, { x: spawnX, y: 1, id: Date.now() + Math.random() }]);
    }, []);

    const moveBow = useCallback((direction) => {
        setBowX(prev => {
            if (direction === 'LEFT' && prev > 1) return prev - 1;
            if (direction === 'RIGHT' && prev < WIDTH - 2) return prev + 1;
            return prev;
        });
    }, []);

    const shootArrow = useCallback(() => {
        if (mode === 'HARD' && arrowsUsed >= arrowLimit) return;

        setArrows(prev => [...prev, { x: bowX, y: HEIGHT - 2, id: Date.now() + Math.random() }]);
        setArrowsUsed(prev => prev + 1);
    }, [bowX, mode, arrowsUsed, arrowLimit]);

    const updateGame = useCallback(() => {
        if (gameState !== 'PLAYING') return;

        frameCount.current++;

        // Spawn balloons
        if (frameCount.current % BALLOON_SPAWN_RATE === 0 && balloonsShot < totalBalloons) {
            // Check active balloons count roughly to avoid overcrowding if needed, 
            // but for now just spawn if we haven't reached the total shot count target
            // The C++ logic checked active < 5, let's replicate that
            setBalloons(prev => {
                if (prev.length < 5) {
                    const spawnX = Math.floor(Math.random() * (WIDTH - 4)) + 2;
                    return [...prev, { x: spawnX, y: 1, id: Date.now() + Math.random() }];
                }
                return prev;
            });
        }

        // Move Balloons
        setBalloons(prev => prev.map(b => ({ ...b, y: b.y + 0.2 })).filter(b => b.y < HEIGHT));

        // Move Arrows
        setArrows(prev => prev.map(a => ({ ...a, y: a.y - 1 })).filter(a => a.y >= 0));

        // Collision Detection
        setArrows(prevArrows => {
            let newArrows = [...prevArrows];
            let hit = false;

            setBalloons(prevBalloons => {
                let newBalloons = [...prevBalloons];

                // Simple collision check
                // Since balloons move fractionally, we check if arrow is close enough
                for (let i = newArrows.length - 1; i >= 0; i--) {
                    for (let j = newBalloons.length - 1; j >= 0; j--) {
                        const arrow = newArrows[i];
                        const balloon = newBalloons[j];

                        if (Math.abs(arrow.x - balloon.x) < 1 && Math.abs(arrow.y - balloon.y) < 1) {
                            newArrows.splice(i, 1);
                            newBalloons.splice(j, 1);
                            setScore(s => s + 10);
                            setBalloonsShot(s => s + 1);
                            hit = true;
                            break; // Arrow can only hit one balloon
                        }
                    }
                    if (hit) {
                        hit = false; // Reset for next arrow
                        continue;
                    }
                }
                return newBalloons;
            });

            return newArrows;
        });

        // Check Game Over
        // We need to check this in a useEffect or here.
        // Since state updates are async, we might not catch it immediately here with current state values.
        // However, for this simple loop, checking refs or using functional updates is better.
        // Let's do a separate check in useEffect for game over to be safe with state.

    }, [gameState, balloonsShot, totalBalloons]);

    useEffect(() => {
        const loop = (time) => {
            if (lastTimeRef.current !== undefined) {
                // const deltaTime = time - lastTimeRef.current;
                // Update game logic
                updateGame();
            }
            lastTimeRef.current = time;
            requestRef.current = requestAnimationFrame(loop);
        };

        if (gameState === 'PLAYING') {
            requestRef.current = requestAnimationFrame(loop);
        }

        return () => cancelAnimationFrame(requestRef.current);
    }, [gameState, updateGame]);

    // Game Over Check
    useEffect(() => {
        if (gameState !== 'PLAYING') return;

        if (balloonsShot >= totalBalloons) {
            setGameState('GAME_OVER');
        } else if (mode === 'HARD') {
            if (arrowsUsed >= arrowLimit && arrows.length === 0) {
                // Check if it's impossible to win (not enough arrows left to kill remaining balloons)
                // For now, just simple check: if out of arrows and no active arrows, game over.
                setGameState('GAME_OVER');
            }
        }
    }, [balloonsShot, totalBalloons, arrowsUsed, arrowLimit, arrows.length, mode, gameState]);

    return {
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
    };
};
