#include "taskstates.h"

TaskStates::TaskStates()
{
    /**
    * All the values of each state get assigned in the constructor
    */
    states["Todo"] = "Todo";
    states["InProgress"] = "In Progress";
    states["InReview"] = "In Review";
    states["Done"] = "Done";
}

QString TaskStates::TodoState(){
    /**
    * Returns the value of TodoState
    */
    return states["Todo"];
}

QString TaskStates::InProgressState(){
    /**
    * Returns the value of InProgressState
    */
    return states["InProgress"];
}

QString TaskStates::InReviewState(){
    /**
    * Returns the value of InReviewState
    */
    return states["InReview"];
}

QString TaskStates::InDoneState(){
    /**
    * Returns the value of InDoneState
    */
    return states["Done"];
}
