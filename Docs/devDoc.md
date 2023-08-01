
<h1 style="text-align: center;"> MeeTimeTracker Application</h1>
<h2 style="text-align:center;">Software Development Documentation</h2>
<center>
Authors:
Shaan Nagra shaan.n@outlook.co.nz 
</center>


# 1. Intro
## Revision history   

| Date       | Version | Change Reference     |
| ---------- | ------- | -------------------- |
| 2023-06-28 | 0.1     | Create Initial Draft | 


**Purpose:**  
The purpose of this document is track information and key details relating to development of the MeDesktopTimer application. A pommodoro like timer, that allows useful additional information to be tracked, such that it can present a virtual representation of the work done in a day. Allow for analysis of data to see break downs for further details.

**Scope:**  
This documents scope covers the requirements, design and planning of the development of the MeDesktopTimer application. Unlike more traditional documentation processes, this document will be more compact and rapidly updated, as the development is expected to be very small relative to traditional applications.
>Note: the scope of this document may lead to more ambiguity and less consistent documentation.  


# 2. Overall Description
>**Purpose:** A pomodoro like timer, that allows useful additional information to be tracked, such that it can present a virtual representation of the work done in a day. Allow for analysis of data to see break downs for further details.

## 2.1 General Description

User need to be able to set timers that run and alert the user when completed. the alert should be run till the user stops it. Alternative ways of tracking time could be stopwatch  based where a user may still need to be alerted that it is running in the background. The user should be able to document what the timer was for in such a manner that it can be used to create reports and analysis of how much time was spent doing what type of work. The details may need to be updated after the fact, so a way to do so needs to also be implemented.

## 2.2 Functions

### Tracking

#### Logging
##### Categorisation
Allow user to categorise the work recorded during the timer running into **projects**. By categorising what the timer is for will allow users to track and report time spent on given tasks.  
Two levels of categorisation (**Subprojects**). Some projects may have more specific tasks that fall under it.  A user may want to see time spent across the different tasks.

##### Descriptions
Allow user to provide a specific description of the task done during the timer. Further flexibility in recording because user may want to go back an get a better idea of what they were actually doing.  

##### Tags
An option of using **tags** that can be associated with tasks for work done. A feature alot of productivity apps use as tags allow quick and easy way of sorting/grouping across multiple categories.  
Not to be use associated with categories. should be able to span across all timers/categories.  
Should be easy to add a new tag quickly and easily. (Simplenotes implementation is a good example).

##### Billing
>NOTE: not know how to be implement this yet so for know this function is left blank. 
   Allow user to flag categories (maybe timers instead). if they are billable. 

#### Timers

##### Countdown Timer (Regular Timer)
Allow user to set a regular timer that runs for a set duration and alerts the user when it ends. Core functionality to recording time.

##### Datetime Timer (Alarm like timer)
Allow user to set a timer based on a specific local time for when the timer will end, and alert the user when it does. Allow user to visualise their time relative to datetime rather than for duration they are going to work.  
Situations where a user may have set time before another task(meetings, erands, end of day, etc.) that they plan to work on a set task.

##### Stopwatch Timer (Non alert just record)
Allow user to start a stopwatch timer that records unttil they are done and then manually stop the timer. Usefull for meetings and other task where the end time is not known.  
Alert user stopwatch is running. Allow user to set a alert function to prevent forgetting that the timer is still running.  
E.g, alert user every 30 minutes. 

##### Pause and Resume Timers.
Allow users to pause a running timer. To prevent users from having to end timers early for small moments where they need to move away from their desk, allow user to **pause** a timer and then **resume** it when they need.

##### Ending Timers.
End a running timer before it is completed. Situations where pausing the timer is not possible, a timer may need to be ended early.

##### saving configurations of timers.
Save configurations of timers, time to run. project, sub-project, tags, description. 
Clear timers, delete saved configurations of timers. 
Load timers, Load a saved configuration to be run. 

> NOTE: do not design with the constraint that would prevent users from running multiple timers. 

## 2.3 Inputs.

Duration - *"the input for a countdown timer."*
* Input:   the time span the timer will run for in hours minutes seconds.
* Input range:   `0:0:1` to `11:59:59`

Alarm time - *"the input for a datetime timer"*
* Input: the hour minutes second of the day that the alarm will run.
* Input range: `current datetime` to `23:59:59 from current datetime`

Pauses
* Record the time between when a timer was paused and resumes as "not work being done"
* Valid pause time duration: `0:0:5`
	* prevent recording useless information where a timer may be paused for insignificant amount of time.

Projects and Subprojects.
* No project needs to be selected (save as non-categorised.)
* No subproject needs to be selected (saves as direct to sub project)

Tags
* No tag needs to be selected. (adds to untagged category)
* Multple tags could be selected. 
	* use simplenote style of tags
	* tag names cannot have spaces.
	* space or enter should input as tag.
	* if input matches existed tags it should highlight them.

# 3. Design
## 3.1 Data Entity Relation
---
### Saved Timers Diagram
![saved timers diagram](./assets/savedTimersER.svg)

---
### Log Run Timer
![logged tiemers diagram](./assets/loggedTimersER.svg)
```
mecountdowntimer.cpp 

data:
	c_hours
	c_minutes
	c_seconds
	c_hms_string
	c_zero
	c_time_remaining
	c_interval_timer
	c_pb_state

fucntions:
	isValidTime
	enableTimeInput
	updateDisplayTime
	updateTime
	connectQTimer
	stopAlarm
	startAlarm
	timerStart
	timerPause
	timerResume
	timerReset
	timerCompleted
	
```

```
data:

c_set_duration
c_time_remaining

functions:
	setDuration
	setTimeRemaining

	isValidDuration

	startTimer
	pauseTimer
	resumeTimer
	resetTimer
	okTimer

	startAlarm
	stopAlarm

```
