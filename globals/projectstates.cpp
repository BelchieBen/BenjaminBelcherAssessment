#include "projectstates.h"

ProjectStates::ProjectStates()
{
    states["NotStarted"] = "Not Started";
    states["InProgress"] = "In Progress";
    states["Completed"] = "Completed";
}

QString ProjectStates::getState(QString state)
{
    return states[state];
}

