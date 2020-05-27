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
## TODO List:
- Automated asset importing
- Networking Callbacks
- Player save (rules) interface
- More debugging
- More commandlet options
- More options of separating speaker audio bucket data
- Animation callbacks
- Extra fx callbacks
- Blueprint Function Override for exposing speaker to outside systems
- Custom fades for starting, stopping, interrupting

----
## Usage

*How To Create A New Instance*

1. Create a new folder in your dialogue instance's module called MyNewSystem

1. Create a new file for your system's types "MyNewSystemTypes.h/.cpp"
	* This types object is a good place to expose any system-wide classes, such as a priority enum

1. Create a new file for your CADialogueInstanceComponent subclass "MyNewSystemInstanceComponent.h/.cpp"
	* The instance component is where you implement any logic, such as looping idle chatter or condition changes

1. Create a new file for your BlueprintFunctionLibrary "MyNewSystemFunctionLibrary.h/.cpp"
	* Implement all the functions any external system would call to trigger an event
	* Such as: PlayIdleChatterFromAnySpeaker() or PlayerEmote(FGameplayTag EmoteTag)

1. Implement the classes, using the examples as a reference

1. Add the gameplay tags and sound data to the instance component

1. Add the gameplay tag to the project settings

1. Add speaker components to your world and implement function library calls on external game systems

----
## Specs
* Unreal Engine 4.24