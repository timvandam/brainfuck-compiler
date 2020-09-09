#pragma once

#include "parser.h"

namespace Optimizer {
    using namespace Parser;
    void optimize(Operation::Scope &program);
    void mergeAdd(Operation::Scope &program);
    void mergeAddPtr(Operation::Scope &program);
}
