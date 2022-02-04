#include "taskstates.h"

TaskStates::TaskStates()
{
    states["Todo"] = "Todo";
    states["InProgress"] = "In Progress";
    states["InReview"] = "In Review";
    states["Done"] = "Done";
}

QString TaskStates::TodoState(){
    return states["Todo"];
}

QString TaskStates::InProgressState(){
    return states["InProgress"];
}

QString TaskStates::InReviewState(){
    return states["InReview"];
}

QString TaskStates::InDoneState(){
    return states["Done"];
}
