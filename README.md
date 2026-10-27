# CS225 Assignment 2 Part 2 - Event Handling Pong

A simple human versus CPU Pong game built on the supplied Entity-Component framework and Alpha Engine

Open `EventHandling-PongGame.sln` in Visual Studio 2022 with the Desktop development with C++ workload and a Windows 10 SDK, select Debug or Release and the x64 platform, then build and run

The provided engine libraries contain x64 objects only, so the solution exposes the supported x64 configurations

The game uses basic C++11 features alongside traditional C++ classes, pointers and loops, with no newer language features in the authored code

## Controls

| Action | Input |
| --- | --- |
| Move up | W or Up arrow |
| Move down | S or Down arrow |
| Stop | Release movement keys |
| Restart | R or Mode > Restart |
| Quit | Ctrl + Q or close the window |

Opposite movement directions cancel and the player stops while the framework menu captures input

## How the handout requirements are met

| Requirement | Implementation |
| --- | --- |
| Extend the Entity-Component framework | Player and CPU inherit from Paddle, which inherits from Entity, while Ball inherits directly from Entity |
| Use components | PositionComponent, MotionComponent and RenderComponent provide position, movement and drawing |
| Keep the player separate from input detection | InputEventManager polls the keyboard and sends a direction-only InputEvent to the Player member handler |
| Use generic event subscriptions | Each subscriber owns an EventHandler instance using the supplied EventHandler template |
| Detect and dispatch collisions | CollisionEventManager extends EventManager and sends CollisionEvent objects for paddles, horizontal walls and open goals |
| Use simple event-driven CPU behavior | A player hit starts vertical tracking, while a CPU hit or either wall hit stops it |
| Keep ball speed constant | Ball reacts to contact events by reversing one velocity component without changing its magnitude |
| Reset the game after a loss | A goal event marks the round as over and the level requests AE_GS_RESTART, freeing and reconstructing all round state |
| Preserve the supplied framework behavior | The original framework implementation is unchanged, with only documentation comments reformatted at the user request |
| Keep the framework menu and clearing code | The level retains the menu, shortcuts and frame-buffer clear operation |

The game advances in small fixed steps and checks paddle-face crossings to avoid skipping a paddle between frames

The ball has a shallow starting angle so the CPU can return shots while keeping the simple stop-on-wall behavior from the example

Entities own their attached components and their event-handler members, while the managers borrow the handler pointers and are destroyed before the entities

All authored gameplay declarations and function descriptions are in `.h` files, with function bodies in `.cc` files and English `//` explanations without sentence-ending periods

Every project and test `.h`, `.hh` and `.cc` file starts with a block containing `@author alvaro.zurinaga` and an English `@brief`

Class and function declarations use a short `/** ... */` block containing only an English `@brief` that describes their purpose without a sentence-ending period

The original framework keeps its supplied `.hh` files and inline template definitions, with its code unchanged and only the requested documentation comments updated

## Verification

The supplied reference material consists of the assignment PDF and the demo executable in `docs`

No official automated tester or fixed expected-output files are included in this repository, and the checks below were added for this implementation

Build the real game in both Debug x64 and Release x64

Run the headless behavioral checks with a C++11-capable MinGW g++ compiler available on PATH

```powershell
.\tests\run-tests.ps1
```

The tests compile the actual gameplay sources using `-std=c++11 -Wall -Wextra -pedantic -Werror`, replacing only keyboard and graphics calls with small test stubs

They cover input aliases, held and released keys, cancelling opposite keys, menu capture, generic event filtering, paddle limits, paddle hits and misses, CPU tracking, both wall reflections, constant speed, both goals, frame timing and repeated round destruction and reconstruction

The rally checks also play the opening serve and five consecutive CPU returns across the full court, including bounces off both horizontal walls

For a manual comparison, run `docs/EventHandling-PongGame.exe`, then run the executable built from this solution and check these behaviors

| Check | Expected behavior |
| --- | --- |
| Move and release the player controls | The player moves up or down and stops when the keys are released |
| Move toward the court edges | The whole paddle remains within the top and bottom boundaries |
| Return the ball to the CPU | The CPU starts following the ball vertically and can return it |
| Observe wall and paddle contacts | The ball reflects without gaining speed |
| Observe the CPU after contacts | Tracking stops on a CPU hit or a top or bottom wall hit |
| Miss on either side | Both paddles, the ball and the CPU tracking state reset for a new round |
| Use restart and quit | R and Mode > Restart reset the round, while Ctrl + Q exits |

Also inspect the code organization because visible gameplay alone cannot verify event-driven separation, component ownership or the declaration and implementation split

Debug linking may report LNK4099 for the supplied engine because its `aecore.pdb` file was not included with the library, while the game still builds and runs

## Submission

Create the required archive for the Moodle username with

```powershell
.\scripts\package-submission.ps1 -Username 'alvaro.zurinaga'
```

The archive includes the source headers and implementations, tests, project files, README and supplied engine dependency so it can be rebuilt after extraction

The resulting file is `submission/cs225fa26_alvaro.zurinaga_2-2.zip`

Generated build output, the reference demo executable and Git metadata are excluded
