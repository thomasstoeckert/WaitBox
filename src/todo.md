# Project Plans
This system is divided into a few logical subsystems:
1. Wait Times Data
2. Display
3. Configuration / Customization

## Wait Times Data
This subsystem holds a cache of the most recent wait times results, provides them
 when requested, and does things
### Initialization
Upon the start of the wait times subsystem, we prepare a buffer for our API
 results and our primary data store.
### Regular Functionality
We've got to refresh our data when requested, sending requests to each park we
 wish to track. This is done in the following process:

For each park:
 * Send the request to get wait times information
 * Filter / parse the request into a JSON document
 * Interpret and store this data into our own data structures

### Data Structures
Attraction:
 * [String] Entity ID
 * [String] Name
 * [String] Status
 * [uint]   Wait Time

Park:
 * [String] Entity ID
 * [String] Name

Attractions are stored in a per-park hashmap, with the Entity ID as the primary 
 key.

Parks are stored in one hashmap, with the Entity ID as the primary key. 

## Display
This module runs the E-INK display, which takes in data from our Wait Times Data
 manager and renders it onto the screen. It manages formatting, takes in config
 information, and handles all communication with the screen. Does not manipulate
 data.
### Initialization
We connect to the screen, creating our display class. If necessary, we can go
 through and draw a splash/welcome screen.
### Regular Functionality
Render:
* Take in a pointer to our park/attraction data, and render what's there

## Configuration / Customization
TODO: Design / Implement this. This is a stretch goal - the primary goal is to
 have just MK parks, or some rough customization based upon Entity IDs
### Initialization
### Regular Functionality

### Data Structures
As of yet, this is a very simple setup

configData:
 * List of four entity park IDs
 * List of four lists of attraction park IDs