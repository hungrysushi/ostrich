#pragma once

#include <memory>

#include "registers.h"
#include "interface/addressable.h"
#include "instructions.h"


class CPU {
    public:
        CPU();
        virtual ~CPU();

        void Boot();
        int Step();
        void Fetch(InstructionContext& context);
        void Decode(InstructionContext& context);
        void Execute(InstructionContext& context);

        // handlers
        void _nop(InstructionContext& context);

        Registers registers_;
        std::shared_ptr<Addressable> memory_;

        uint64_t cycles_ = 0;

        // state
        bool ime_ = false;
        bool setImeNextCycle_ = false;
        bool halted_ = false;
        uint8_t ie_ = 0x00;
        uint8_t if_ = 0x00;
};


