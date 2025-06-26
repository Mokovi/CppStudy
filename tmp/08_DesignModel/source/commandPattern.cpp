#include "commandPattern.h"


void CommandManager::executeCommand(std::unique_ptr<Command> cmd) {
    cmd->execute();
    history.push(std::move(cmd));
}
void CommandManager::undo() {
    if (!history.empty()) {
        history.top()->undo();
        history.pop();
    }
}