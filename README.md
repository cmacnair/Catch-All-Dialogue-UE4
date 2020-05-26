# Catch All Dialogue

----
## What is Catch All Dialogue?
It's a plugin for Unreal Engine 4 that provides a framework for composing **expressive game audio dialogue systems**.

The dialogue subsystem handles all the complexity for concurrent dialogue systems and dynamic speaker priorities. See the image below for a high level overview.

![Image of High Level Overview](https://github.com/cmacnair/Catch-All-Dialogue-UE4/blob/master/doc/High%20Level%20Overview.png)

For creating a new dialogue instance, see the diagram below for subclassing requirements:
![Image of Subclassing Overview](https://github.com/cmacnair/Catch-All-Dialogue-UE4/blob/master/doc/Subclassing%20Overview.png)

----
## What problems does it solve? Why use this framework?
* Setting up concurrent dialogue systems in games can be tricky. This system provides a catch all solution to effectively managing complexities that arise.
* It allows the game developer to focus only on the game-specific implementation.
* By nature it encourages expressive and consistent implementation details.
* For medium to large size games, there can easily be thousands of dialogue assets. This system helps manage the memory and lifetime of these assets under the hood.
* Provides a clean and concise API, so designers that work in Blueprints will make clear communication to the system.

----
## Features
* Operates as a Game Instance Subsystem, so everything can be persistent and globally accessible
* Easily add Rules to your dialogue system
* Easily import data from spreadsheets
* Commandlet interface for getting usage stats
* Rich debugging interface for pinpointing odd behavior
* Provides examples to clearly show how it can be used
* Liberal use of Gameplay Tags so data can be changed easily by anyone on your team

----
## Usage
* @todo

----
## Specs
* Unreal Engine 4.24