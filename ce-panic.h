#pragma once

#include "ce-base.h"

[[noreturn]] void ce_panic(ce_cstr msg);

void ce_debug(ce_cstr msg);
