#pragma once

#include <memory>

#include "registers.h"
#include "interface/addressable.h"
#include "instructions.h"


class CPU : public Addressable {
    public:
        CPU();
        virtual ~CPU();

        void Boot();
        int Step();
        void Fetch(InstructionContext& context);
        void Decode(InstructionContext& context);
        void Execute(InstructionContext& context);

        const uint8_t Read(const uint16_t addr);
        void Write(const uint16_t addr, const uint8_t value);

        // handlers
        void _nop(InstructionContext& context);
        void _jp(InstructionContext& context);
        void _xor(InstructionContext& context);
        void _ld16(InstructionContext& context);
        void _ld(InstructionContext& context); // can this cover all ld types?
        void _dec(InstructionContext& context);
        void _inc(InstructionContext& context);
        void _jr(InstructionContext& context);
        void _di(InstructionContext& context);
        void _ei(InstructionContext& context);
        void _ldh(InstructionContext& context);
        void _halt(InstructionContext& context);
        void _cp(InstructionContext& context);
        void _rst(InstructionContext& context);
        void _add(InstructionContext& context);
        void _adc(InstructionContext& context);
        void _pop(InstructionContext& context);
        void _sub(InstructionContext& context);
        void _sbc(InstructionContext& context);
        void _and(InstructionContext& context);
        void _or(InstructionContext& context);
        void _inc16(InstructionContext& context);
        void _dec16(InstructionContext& context);
        void _add16(InstructionContext& context);
        void _push(InstructionContext& context);
        void _rlca(InstructionContext& context);
        void _rrca(InstructionContext& context);
        void _rla(InstructionContext& context);
        void _rra(InstructionContext& context);
        void _daa(InstructionContext& context);
        void _cpl(InstructionContext& context);
        void _scf(InstructionContext& context);
        void _ccf(InstructionContext& context);
        void _stop(InstructionContext& context);
        void _ret(InstructionContext& context);
        void _reti(InstructionContext& context);
        void _call(InstructionContext& context);
        void _addSpR8(InstructionContext& context);
        void _ldHlSpR8(InstructionContext& context);
        void _ldSpHl(InstructionContext& context);
        void _ldA16Sp(InstructionContext& context);
        void _prefixCb(InstructionContext& context);

        // helpers
        uint16_t _readData(ArgumentType argumentType);
        uint8_t _readMem(uint16_t addr);
        uint16_t _readImm16();
        uint8_t _readImm8();
        bool _checkCondition(ConditionType conditionType);
        void _writeData(ArgumentType argumentType, uint16_t data);
        void _writeMem(uint16_t addr, uint8_t data);
        void _stackPush(uint8_t data);
        void _stackPushWord(uint16_t data);
        uint8_t _stackPop();
        uint16_t _stackPopWord();
        void _savePCToStack();


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


