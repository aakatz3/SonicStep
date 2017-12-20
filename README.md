## MVP Abstract
**Fixing accelerometers to sneakers enables us to collect data along three axes.  By normalizing the data and running it through high-pass filters, we eliminate sensor jitter and ultra-long slow trends.  We run an analysis to correlate this data with sonic frequencies, and transmit the pitch over bluetooth to an LED strip display board for the visualization component.  Simultaneously, we set a voice on a synth chip to play a specified note in accordance with the pitch acquired.  Thus, we have created a sensory experience for both the eyes and the ears through physical motion!**

[_SonicStep.  Move the music._](https://youtu.be/XC2DmUyljfs)

_______________________________________________________________________________________________________

## Inspiration
Tired of DJs and Spotify shuffle alike playing songs that don't fit the situation at all, we've resorted to generating our own tunes in a foolproof way. 

## What it does
Utilizes a BNO055 accelerometer wired to an Arduino to take in orientation data on 9 axes. We scale the values of each axis, and use the scaled version to determine the intensity of each the three colors on the RGB LED. We then transmit the accelerometer values using HC-05 bluetooth modules to a second Arduino, which monitors the values and synthesizes the music. Three buttons on the second station are used to program which song is played.

## How we built it
Using the BNO055, 2 Arduino Uno R3s, 2 RGB LEDs, 3 pushbuttons, 3.5mm audio jack for output, 1 breadboard, 1 Arduino Protoshield.
We secided to solder together the parts on the shoe for durability, but as the base-station synthesizer will likely change drastically, we chose to use a breadboard for it.

## Challenges we ran into
Initially we were set on utilizing a synth chip to generate our own melodious-sounding notes from the calculated frequencies, but we were unable to procure one within the time and monetary constraints of the project.  Instead, we had to modify the scope of our design to focus on setting the beat and duration of pre-programmed music as opposed to programming it via motion.

## Accomplishments that we're proud of
A perfectly functional final product!
We also were able to detect footsteps, and work within a limited budget.

## What we learned
How to seamlessly incorporate bluetooth technology into designs for ease of use in the real world (no one is going to connect a shoe with wire to a speaker!)
Also, how to collaborate with one another coming from different backgrounds and areas of expertise. 

## What's next
So much!  Our vision for SonicStep has two major future routes.  
1. Creating a mobile app that similarly connects via bluetooth to a custom shoe that syncs the music from your iPhone based on the acceleration data as you run (or walk - we're not judging).  It's the perfect soundtrack to narrate your life!  This would not require anything but minor tweaks on the backend, as well as frontend implementation (probably via Swift).  Are we feeling a whole new line of fresh, hopping kicks?!?!
2. Changing the dance class game!  With each dancer equipped with SonicSteps, a harmonious ~reversed~ possibility is completely viable.  It's like a cappella... but entirely from SHOES.  No one could ever be off beat, and the results would be both revolutionary and beautiful.
