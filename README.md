### Description
### Autons
### User Control
### Ports 

### Description
This program is the only program that 4303X is using this year. There are a few disadvantages to this, but they are quickly out-weighed by the advantages. The autonomous selector is one of the many things that will make this file format much easier than having multiple repositories.

### Autons
There are currently only two autons planned for this year. One starts on the alliance's offensive zone, and the other starts in the opposing zone. The opposing zone's auton is planned to score 3 triballs, including the preload. The alliance zone's auton is planned to score 2-3 triballs, and end touching the elevation bar (for AWP). The AWP auton is risky, as it relies on us shooting triballs across the field. This could lead to us hitting our alliance partner and messing up their auton, which is something we will have to plan for before matches. Another potential issue with the AWP auton is that our robot enters the neutral zone. Though our PID should prevent us from being knocked off course, it could still be an issue.

### User Control
We use a tank drive with 6 motors, 2 of which are PTO motors. We also have a linear puncher, an intake, and an end game. The linear puncher and intake recieve 2 5.5-volt motors each, and the end game uses the 2 PTO motors. The PTO should only be activated during the AWP auton and at the end of the game, which is why the activation will require 2 buttons instead of 1. 

### Ports
Note: A negative sign means that the port is reversed
Left PTO = 2,
Left Back = -1,
Left Front = -3,
Right PTO = -7,
Right Back = 8,
Right Front = 10,
Intake Left = ?,
Intake Right = 5,
Puncher Left = ?,
Puncher Right = ?,
IMU = 17