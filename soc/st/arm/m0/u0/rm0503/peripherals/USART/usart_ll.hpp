#pragma once

/*
 *	Name: usart_ll.hpp
 *
 *  Copyright (c) Mateusz Semegen and contributors. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for details.
 */

// std
#include <type_traits>

// cmsis
#include <stm32u0xx.h>

// xmcu
#include <xmcu/non_constructible.hpp>
#include <xmcu/non_copyable.hpp>

// soc
#include <soc/st/arm/m0/u0/rm0503/peripherals/USART/base.hpp>

namespace soc::st::arm::m0::u0::rm0503::peripherals::ll {
struct usart_cr1_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        ue = USART_CR1_UE,
        uesm = USART_CR1_UESM,
        re = USART_CR1_RE,
        te = USART_CR1_TE,
        idleie = USART_CR1_IDLEIE,
        rxneie = USART_CR1_RXNEIE,
        tcie = USART_CR1_TCIE,
        txeie = USART_CR1_TXEIE,
        peie = USART_CR1_PEIE,
        ps = USART_CR1_PS,
        pce = USART_CR1_PCE,
        wake = USART_CR1_WAKE,
        m0 = USART_CR1_M0,
        mme = USART_CR1_MME,
        cmie = USART_CR1_CMIE,
        over8 = USART_CR1_OVER8,
        rtoie = USART_CR1_RTOIE,
        eobie = USART_CR1_EOBIE,
        m1 = USART_CR1_M1,
        fifoen = USART_CR1_FIFOEN,
        txfeie = USART_CR1_TXFEIE,
        rxffie = USART_CR1_RXFFIE
    };

    enum class Shift_5_bit_value : std::uint32_t
    {
        dedt = 16u,
        deat = 21u,
    };

    enum class Mask_5_bit_value : std::uint32_t
    {
        dedt = 0x1Fu,
        deat = 0x1Fu
    };
};
struct usart_cr2_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        slven = USART_CR2_SLVEN,
        dis_nss = USART_CR2_DIS_NSS,
        addm7 = USART_CR2_ADDM7,
        lbdl = USART_CR2_LBDL,
        lbdie = USART_CR2_LBDIE,
        lbcl = USART_CR2_LBCL,
        cpha = USART_CR2_CPHA,
        cpol = USART_CR2_CPOL,
        clken = USART_CR2_CLKEN,
        linen = USART_CR2_LINEN,
        swap = USART_CR2_SWAP,
        rxinv = USART_CR2_RXINV,
        txinv = USART_CR2_TXINV,
        datainv = USART_CR2_DATAINV,
        msbfirst = USART_CR2_MSBFIRST,
        abren = USART_CR2_ABREN,
        roten = USART_CR2_RTOEN
    };

    enum class Shift_stop_value : std::uint32_t
    {
        stop = 12u
    };
    enum class Shift_abrmod_value : std::uint32_t
    {
        abrdmod = 21u
    };
    enum class Shift_add_value : std::uint32_t
    {
        add = 24u
    };

    enum class Value_stop : std::uint32_t
    {
        stop_1_bit = 0x0u,
        stop_0_5_bit = 0x1u,
        stop_2_bit = 0x2u,
        stop_1_5_bit = 0x3u
    };
    enum class Value_abrmod : std::uint32_t
    {
        abrmod_start_bit = 0x0u,
        abrmod_falling_edge = 0x1u,
        abrmod_0x7FF = 0x2u,
        abrmod_0x55 = 0x3u
    };

    enum class Mask_abrmod : std::uint32_t
    {
        abrmod_mask = 0x3u
    };
    enum class Mask_stop : std::uint32_t
    {
        stop_mask = 0x3u
    };
    enum class Mask_add : std::uint32_t
    {
        add_mask = 0xFFu
    };
};
struct usart_cr3_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        none = 0x0u,
        eie = USART_CR3_EIE,
        iren = USART_CR3_IREN,
        irlp = USART_CR3_IRLP,
        hdsel = USART_CR3_HDSEL,
        nack = USART_CR3_NACK,
        scen = USART_CR3_SCEN,
        dmar = USART_CR3_DMAR,
        dmat = USART_CR3_DMAT,
        rtse = USART_CR3_RTSE,
        ctse = USART_CR3_CTSE,
        ctsie = USART_CR3_CTSIE,
        onebit = USART_CR3_ONEBIT,
        ovrdis = USART_CR3_OVRDIS,
        ddre = USART_CR3_DDRE,
        dem = USART_CR3_DEM,
        dep = USART_CR3_DEP,
        wufie = USART_CR3_WUFIE,
        txftie = USART_CR3_TXFTIE,
        tcbgtie = USART_CR3_TCBGTIE,
        rxftie = USART_CR3_RXFTIE,
    };

    enum class Shift_scarcnt_value : std::uint32_t
    {
        scarcnt = 12u
    };
    enum class Shift_wus_value : std::uint32_t
    {
        wus = 20u
    };
    enum class Shift_rxftcfg_value : std::uint32_t
    {
        rxftcfg = 25u
    };
    enum class Shift_txftcfg_value : std::uint32_t
    {
        txftcfg = 29u
    };

    enum class Value_wus : std::uint32_t
    {
        address_match = 0x0u,
        start_bit = 0x2u,
        rxne = 0x3u
    };
    enum class Value_txftcfg_rxftcfg_value : std::uint32_t
    {
        _1_8 = 0x0u,
        _1_4,
        _1_2,
        _3_4,
        _7_8,
        full
    };

    enum class Mask_scarcnt : std::uint32_t
    {
        scarcnt = 0x7u
    };
    enum class Mask_wus : std::uint32_t
    {
        wus = 0x3u
    };
    enum class Mask_rxftcfg : std::uint32_t
    {
        rxftcfg = 0x5u
    };
    enum class Mask_txftcfg : std::uint32_t
    {
        txftcfg = 0x5u
    };
};
struct usart_brr_descriptor : private xmcu::non_constructible
{
};
struct usart_gtpr_descriptor : private xmcu::non_constructible
{
    enum class Shift_psc_gt : std::uint32_t
    {
        psc = 0u,
        gt = 8u
    };
};
struct usart_rtor_descriptor : private xmcu::non_constructible
{
    enum class Shift_rto : std::uint32_t
    {
        rto = 0u,
    };
    enum class Shift_blen : std::uint32_t
    {
        blen = 24u
    };
};
struct usart_rqr_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        abrrq = 0u,
        sbkrq,
        mmrq,
        rxfrq,
        txfrq
    };
};
struct usart_isr_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        none = 0x0u,
        pe = USART_ISR_PE,
        fe = USART_ISR_FE,
        ne = USART_ISR_NE,
        ore = USART_ISR_ORE,
        idle = USART_ISR_IDLE,
        rxne = USART_ISR_RXNE_RXFNE,
        tc = USART_ISR_TC,
        txe = USART_ISR_TXE_TXFNF,
        lbdf = USART_ISR_LBDF,
        ctsif = USART_ISR_CTSIF,
        cts = USART_ISR_CTS,
        rtof = USART_ISR_EOBF,
        eobf = USART_ISR_EOBF,
        udr = USART_ISR_UDR,
        abre = USART_ISR_ABRE,
        abrf = USART_ISR_ABRF,
        busy = USART_ISR_BUSY,
        cmf = USART_ISR_CMF,
        sbkf = USART_ISR_SBKF,
        rwu = USART_ISR_RWU,
        wuf = USART_ISR_WUF,
        teack = USART_ISR_TEACK,
        reack = USART_ISR_REACK,
        txfe = USART_ISR_TXFE,
        rxff = USART_ISR_RXFF,
        tcbgt = USART_ISR_TCBGT,
        rxft = USART_ISR_RXFT,
        txft = USART_ISR_TXFT
    };
};
struct usart_icr_descriptor : private xmcu::non_constructible
{
    enum class Flag : std::uint32_t
    {
        pecf = USART_ICR_PECF,
        fecf = USART_ICR_FECF,
        necf = USART_ICR_NECF,
        orecf = USART_ICR_ORECF,
        idlecf = USART_ICR_IDLECF,
        txfecf = USART_ICR_TXFECF,
        tccf = USART_ICR_TCCF,
        tcbgtcf = USART_ICR_TCBGTCF,
        lbdcf = USART_ICR_LBDCF,
        ctscf = USART_ICR_CTSCF,
        rtocf = USART_ICR_RTOCF,
        eobcf = USART_ICR_EOBCF,
        udrcf = USART_ICR_UDRCF,
        cmcf = USART_ICR_CMCF,
        wucf = USART_ICR_WUCF
    };
};
struct usart_rdr_descriptor : private xmcu::non_constructible
{
};
struct usart_tdr_descriptor : private xmcu::non_constructible
{
};
struct usart_presc_descriptor : private xmcu::non_constructible
{
    enum class Mask : std::uint32_t
    {
        presc = 0xFu
    };

    enum class Shift_value : std::uint32_t
    {
        presc = 0x0u
    };

    enum class Value : std::uint32_t
    {
        _1 = 0x0u,
        _2,
        _4,
        _6,
        _8,
        _10,
        _12,
        _16,
        _32,
        _64,
        _128,
        _256
    };
};

struct usart_clock : private xmcu::non_constructible
{
    enum class Stop_mode_activity
    {
        disable,
        enable
    };

    template<usart_base::Id id_t, typename Source_t> static void enable(Stop_mode_activity stop_mode_a) = delete;
    template<usart_base::Id id_t> static void disable() = delete;

    template<usart_base::Id id_t> [[nodiscard]] static bool is_enabled() = delete;
    template<usart_base::Id id_t, typename Source_t> [[nodiscard]] static bool is_source_selected() = delete;
    template<usart_base::Id id_t> [[nodiscard]] static Stop_mode_activity get_stop_mode_activity() = delete;
};

struct usart : public usart_base
{
private:
    template<typename, typename = std::void_t<>> struct has_enum_flag : std::false_type
    {
    };

    template<typename Type_t> struct has_enum_flag<Type_t, std::void_t<typename Type_t::Flag>> : std::true_type
    {
    };

    /*
     * W - write, R - read, C - clear
     */
    template<typename desc_t> struct Reg_wrc
    {
    public:
        enum class Data : std::uint32_t;

        void zero()
        {
            this->v = static_cast<Data>(0x0u);
        }

        operator const Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

        operator volatile Data&()
        {
            return this->v;
        }
        operator volatile Data*()
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };
    template<typename desc_t> struct Reg_r
    {
        enum class Data;

        Reg_r(const volatile Reg_r& a)
            : v(a.v)
        {
        }

        operator const Data() const
        {
            return this->v;
        }
        operator const Data*() const
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };
    struct Reg_wc
    {
        enum class Data;

        void zero()
        {
            this->v = static_cast<Data>(0x0u);
        }

        constexpr operator Data() volatile const
        {
            return this->v;
        }
        operator const volatile Data*() const
        {
            return &(this->v);
        }

        operator volatile Data&()
        {
            return this->v;
        }
        operator volatile Data*()
        {
            return &(this->v);
        }

    protected:
        volatile Data v;
    };

public:
    struct CR1 : public Reg_wrc<usart_cr1_descriptor>
    {
        using Flag = usart_cr1_descriptor::Flag;
        using enum Flag;

        struct mask : private xmcu::non_constructible
        {
            using enum usart_cr1_descriptor::Mask_5_bit_value;
        };
        struct shift : private xmcu::non_constructible
        {
            using enum usart_cr1_descriptor::Shift_5_bit_value;
        };

        using Data = Reg_wrc<usart_cr1_descriptor>::Data;

        CR1& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
        CR1& operator=(Flag value_a)
        {
            this->v = static_cast<Data>(value_a);
            return *this;
        }
    };
    struct CR2 : public Reg_wrc<usart_cr2_descriptor>
    {
        using Flag = usart_cr2_descriptor::Flag;
        using enum usart_cr2_descriptor::Flag;

        struct mask : private xmcu::non_constructible
        {
            using enum usart_cr2_descriptor::Mask_abrmod;
            using enum usart_cr2_descriptor::Mask_add;
            using enum usart_cr2_descriptor::Mask_stop;
        };

        struct shift : private xmcu::non_constructible
        {
            using enum usart_cr2_descriptor::Shift_abrmod_value;
            using enum usart_cr2_descriptor::Shift_add_value;
            using enum usart_cr2_descriptor::Shift_stop_value;
        };

        struct value : private xmcu::non_constructible
        {
            using enum usart_cr2_descriptor::Value_abrmod;
            using enum usart_cr2_descriptor::Value_stop;
        };

        using Data = Reg_wrc<usart_cr2_descriptor>::Data;

        CR2& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
        CR2& operator=(Flag value_a)
        {
            this->v = static_cast<Data>(value_a);
            return *this;
        }
    };
    struct CR3 : public Reg_wrc<usart_cr3_descriptor>
    {
        using Flag = usart_cr3_descriptor::Flag;
        using enum usart_cr3_descriptor::Flag;

        struct mask : private xmcu::non_constructible
        {
            using enum usart_cr3_descriptor::Mask_rxftcfg;
            using enum usart_cr3_descriptor::Mask_scarcnt;
            using enum usart_cr3_descriptor::Mask_txftcfg;
            using enum usart_cr3_descriptor::Mask_wus;
        };

        struct shift : private xmcu::non_constructible
        {
            using enum usart_cr3_descriptor::Shift_rxftcfg_value;
            using enum usart_cr3_descriptor::Shift_scarcnt_value;
            using enum usart_cr3_descriptor::Shift_txftcfg_value;
            using enum usart_cr3_descriptor::Shift_wus_value;
        };

        struct value : private xmcu::non_constructible
        {
            using enum usart_cr3_descriptor::Value_txftcfg_rxftcfg_value;
            using enum usart_cr3_descriptor::Value_wus;
        };

        using Data = Reg_wrc<usart_cr3_descriptor>::Data;

        CR3& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
        CR3& operator=(Flag value_a)
        {
            this->v = static_cast<Data>(value_a);
            return *this;
        }
    };
    struct BRR : public Reg_wrc<usart_brr_descriptor>
    {
        BRR& operator=(std::uint16_t value_a)
        {
            this->v = static_cast<Data>(static_cast<std::uint32_t>(value_a) & 0xFFFFu);
            return *this;
        }
    };
    struct GTPR : public Reg_wrc<usart_gtpr_descriptor>
    {
        using Data = Reg_wrc<usart_gtpr_descriptor>::Data;

        struct shift : private xmcu::non_constructible
        {
            using enum usart_gtpr_descriptor::Shift_psc_gt;
        };

        GTPR& operator=(Data value_a)
        {
            this->v = static_cast<Data>(static_cast<std::uint32_t>(value_a));
            return *this;
        }
    };
    struct RTOR : public Reg_wrc<usart_rtor_descriptor>
    {
        struct mask : private xmcu::non_constructible
        {
        };
        struct shift : private xmcu::non_constructible
        {
            using enum usart_rtor_descriptor::Shift_blen;
            using enum usart_rtor_descriptor::Shift_rto;
        };

        using Data = Reg_wrc<usart_rtor_descriptor>::Data;

        RTOR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct RQR : public Reg_wrc<usart_rqr_descriptor>
    {
        using Flag = usart_rqr_descriptor::Flag;
        using enum Flag;

        using Data = Reg_wrc<usart_rqr_descriptor>::Data;

        RQR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct ISR : public Reg_r<usart_isr_descriptor>
    {
        using Flag = usart_isr_descriptor::Flag;
        using enum Flag;

        using Data = Reg_r<usart_isr_descriptor>::Data;

        ISR(const volatile ISR& a)
            : Reg_r<usart_isr_descriptor>(a)
        {
        }
    };
    struct ICR : public Reg_wc
    {
        using Flag = usart_icr_descriptor::Flag;
        using enum Flag;

        using Data = Reg_wc::Data;

        ICR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };
    struct RDR : public Reg_wrc<usart_rdr_descriptor>
    {
        using Data = Reg_wrc<usart_rdr_descriptor>::Data;

        RDR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }

        operator std::uint32_t() const
        {
            return static_cast<std::uint32_t>(this->v);
        }
    };
    struct TDR : public Reg_wrc<usart_tdr_descriptor>
    {
        using Data = Reg_wrc<usart_tdr_descriptor>::Data;

        TDR& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
        TDR& operator=(std::uint32_t value_a)
        {
            this->v = static_cast<Data>(value_a);
            return *this;
        }
    };
    struct PRESC : public Reg_wrc<usart_presc_descriptor>
    {
        struct mask : private xmcu::non_constructible
        {
            using enum usart_presc_descriptor::Mask;
        };

        struct shift : private xmcu::non_constructible
        {
            using enum usart_presc_descriptor::Shift_value;
        };

        struct value : private xmcu::non_constructible
        {
            using enum usart_presc_descriptor::Value;
        };

        using Data = Reg_wrc<usart_presc_descriptor>::Data;

        PRESC& operator=(Data value_a)
        {
            this->v = value_a;
            return *this;
        }
    };

    struct Registers : private xmcu::non_copyable
    {
        CR1 cr1;     // control register 1
        CR2 cr2;     // control register 2
        CR3 cr3;     // control register 3
        BRR brr;     // baud rate register
        GTPR gtpr;   // guard time and prescaler register
        RTOR rtor;   // receiver Time Out register
        RQR rqr;     // request register
        ISR isr;     // interrupt and status register
        ICR icr;     // interrupt flag Clear register
        RDR rdr;     // receive Data register
        TDR tdr;     // transmit Data register
        PRESC presc; // clock Prescaler register
    };

    template<usart::Id id_t> [[nodiscard]] constexpr static Registers* registers() = delete;
};

#if defined XMCU_USART1_PRESENT
template<> [[nodiscard]] inline constexpr usart::Registers* usart::registers<usart::_1>()
{
    return reinterpret_cast<usart::Registers*>(USART1_BASE);
}

template<> inline void usart_clock::enable<usart_base::_1, oscillators::hsi16>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0) &&
           true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, oscillators::lse>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, oscillators::lse>()
{
    return xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0 | RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_1, clocks::sysclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART1SEL, RCC_CCIPR_USART1SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_1, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_0) &&
           false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART1SEL_1);
}
template<> inline void usart_clock::disable<usart_base::_1>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR2), RCC_APBSMENR2_USART1SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART1SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR2), RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_1>()
{
    return xmcu::bit::flag::is(RCC->APBENR2, RCC_APBENR2_USART1EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_1>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR2, RCC_APBSMENR2_USART1SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART2_PRESENT
template<> [[nodiscard]] inline constexpr usart::Registers* usart::registers<usart::_2>()
{
    return reinterpret_cast<usart::Registers*>(USART2_BASE);
}

template<> inline void usart_clock::enable<usart_base::_2, oscillators::hsi16>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, oscillators::hsi16>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0) &&
           true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, oscillators::lse>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, oscillators::lse>()
{
    return xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, clocks::pclk>()
{
    return false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0 | RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::enable<usart_base::_2, clocks::sysclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->CCIPR), RCC_CCIPR_USART2SEL, RCC_CCIPR_USART2SEL_0);
    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_2, clocks::sysclk>()
{
    return true == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_0) &&
           false == xmcu::bit::flag::is(RCC->CCIPR, RCC_CCIPR_USART2SEL_1);
}
template<> inline void usart_clock::disable<usart_base::_2>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART2SMEN);
    xmcu::bit::flag::clear(&(RCC->CCIPR), RCC_CCIPR_USART2SEL);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_2>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART2EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_2>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART2SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART3_PRESENT
template<> [[nodiscard]] inline constexpr usart::Registers* usart::registers<usart::_3>()
{
    return reinterpret_cast<usart::Registers*>(USART3_BASE);
}

template<> inline void usart_clock::enable<usart_base::_3, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_3, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, oscillators::lse>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_3, clocks::sysclk>()
{
    return false;
}
template<> inline void usart_clock::disable<usart_base::_3>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART3SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_3>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART3EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_3>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART3SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif
#if defined XMCU_USART4_PRESENT
template<> [[nodiscard]] inline constexpr usart::Registers* usart::registers<usart::_4>()
{
    return reinterpret_cast<usart::Registers*>(USART4_BASE);
}

template<> inline void usart_clock::enable<usart_base::_4, clocks::pclk>(Stop_mode_activity stop_mode_a)
{
    switch (stop_mode_a)
    {
        case Stop_mode_activity::disable:
            xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
        case Stop_mode_activity::enable:
            xmcu::bit::flag::set(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
            break;
    }

    xmcu::bit::flag::set(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_source_selected<usart_base::_4, clocks::pclk>()
{
    return true;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, oscillators::hsi16>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, oscillators::lse>()
{
    return false;
}
template<> [[nodiscard]] inline constexpr bool usart_clock::is_source_selected<usart_base::_4, clocks::sysclk>()
{
    return false;
}
template<> inline void usart_clock::disable<usart_base::_4>()
{
    xmcu::bit::flag::clear(&(RCC->APBSMENR1), RCC_APBSMENR1_USART4SMEN);
    xmcu::bit::flag::clear(&(RCC->APBENR1), RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline bool usart_clock::is_enabled<usart_base::_4>()
{
    return xmcu::bit::flag::is(RCC->APBENR1, RCC_APBENR1_USART4EN);
}
template<> [[nodiscard]] inline usart_clock::Stop_mode_activity usart_clock::get_stop_mode_activity<usart_base::_4>()
{
    return true == xmcu::bit::flag::is(RCC->APBSMENR1, RCC_APBSMENR1_USART4SMEN) ? Stop_mode_activity::enable : Stop_mode_activity::disable;
}
#endif

constexpr usart::CR1::Data operator|(usart::CR1::Flag left_a, usart::CR1::Flag right_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR1::Data operator|(usart::CR1::Data left_a, usart::CR1::Data right_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR1::Data operator|(usart::CR1::Flag flag_a, usart::CR1::Data value_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR1::Data operator|(usart::CR1::Data value_a, usart::CR1::Flag flag_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR1::Flag operator&(usart::CR1::Flag flag_a, usart::CR1::Data value_a)
{
    return static_cast<usart::CR1::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR1::Flag operator&(usart::CR1::Data value_a, usart::CR1::Flag flag_a)
{
    return static_cast<usart::CR1::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR1::Data operator&(usart::CR1::Data value_a, usart::CR1::Data flag_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR1::Data operator<<(xmcu::Limited<std::uint32_t, 0x0u, 0x1Fu> value_a, usart_cr1_descriptor::Shift_5_bit_value shift_a)
{
    return static_cast<usart::CR1::Data>(value_a << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR1::Data operator<<(usart_cr1_descriptor::Mask_5_bit_value mask_a, usart_cr1_descriptor::Shift_5_bit_value shift_a)
{
    return static_cast<usart::CR1::Data>(static_cast<std::uint32_t>(mask_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR1::Flag operator~(usart::CR1::Flag flag_a)
{
    return static_cast<usart::CR1::Flag>((~static_cast<std::uint32_t>(flag_a)));
}
constexpr usart::CR1::Data operator~(usart::CR1::Data flag_a)
{
    return static_cast<usart::CR1::Data>((~static_cast<std::uint32_t>(flag_a)));
}

constexpr usart::CR2::Data operator|(usart::CR2::Flag left_a, usart::CR2::Flag right_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR2::Data operator|(usart::CR2::Data left_a, usart::CR2::Data right_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR2::Data operator|(usart::CR2::Flag flag_a, usart::CR2::Data value_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR2::Data operator|(usart::CR2::Data value_a, usart::CR2::Flag flag_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR2::Flag operator&(usart::CR2::Flag flag_a, usart::CR2::Data value_a)
{
    return static_cast<usart::CR2::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR2::Flag operator&(usart::CR2::Data value_a, usart::CR2::Flag flag_a)
{
    return static_cast<usart::CR2::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR2::Data operator<<(usart_cr2_descriptor::Value_abrmod value_a, usart_cr2_descriptor::Shift_abrmod_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR2::Data operator<<(usart_cr2_descriptor::Value_stop value_a, usart_cr2_descriptor::Shift_stop_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR2::Data operator<<(xmcu::Limited<std::uint32_t, 0x0u, 0x1Fu> value_a, usart_cr2_descriptor::Shift_add_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR2::Data operator<<(usart_cr2_descriptor::Mask_abrmod mask_a, usart_cr2_descriptor::Shift_abrmod_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(mask_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR2::Data operator<<(usart_cr2_descriptor::Mask_add mask_a, usart_cr2_descriptor::Shift_abrmod_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(mask_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR2::Data operator<<(usart_cr2_descriptor::Mask_stop mask_a, usart_cr2_descriptor::Shift_abrmod_value shift_a)
{
    return static_cast<usart::CR2::Data>(static_cast<std::uint32_t>(mask_a) << static_cast<std::uint32_t>(shift_a));
}

constexpr usart::CR3::Data operator|(usart::CR3::Flag left_a, usart::CR3::Flag right_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR3::Data operator|(usart::CR3::Data left_a, usart::CR3::Data right_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::CR3::Data operator|(usart::CR3::Flag flag_a, usart::CR3::Data value_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR3::Data operator|(usart::CR3::Data value_a, usart::CR3::Flag flag_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR3::Flag operator&(usart::CR3::Flag flag_a, usart::CR3::Data value_a)
{
    return static_cast<usart::CR3::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR3::Flag operator&(usart::CR3::Data value_a, usart::CR3::Flag flag_a)
{
    return static_cast<usart::CR3::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR3::Data operator&(usart::CR3::Data value_a, usart::CR3::Data flag_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Value_txftcfg_rxftcfg_value value_a,
                                      usart_cr3_descriptor::Shift_rxftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Value_txftcfg_rxftcfg_value value_a,
                                      usart_cr3_descriptor::Shift_txftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Value_wus value_a, usart_cr3_descriptor::Shift_wus_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(xmcu::Limited<std::uint32_t, 0x0u, 0x7u> value_a, usart_cr3_descriptor::Shift_scarcnt_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Mask_rxftcfg value_a, usart_cr3_descriptor::Shift_rxftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Mask_scarcnt value_a, usart_cr3_descriptor::Shift_rxftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Mask_txftcfg value_a, usart_cr3_descriptor::Shift_rxftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Data operator<<(usart_cr3_descriptor::Mask_wus value_a, usart_cr3_descriptor::Shift_rxftcfg_value shift_a)
{
    return static_cast<usart::CR3::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::CR3::Flag operator~(usart::CR3::Flag flag_a)
{
    return static_cast<usart::CR3::Flag>((~static_cast<std::uint32_t>(flag_a)));
}
constexpr usart::CR3::Data operator~(usart::CR3::Data flag_a)
{
    return static_cast<usart::CR3::Data>((~static_cast<std::uint32_t>(flag_a)));
}

constexpr usart::GTPR::Data operator|(usart::GTPR::Data left_a, usart::GTPR::Data right_a)
{
    return static_cast<usart::GTPR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::GTPR::Data operator<<(xmcu::Limited<std::uint32_t, 0x1u, 0xFFu> value_a, usart_gtpr_descriptor::Shift_psc_gt shift_a)
{
    return static_cast<usart::GTPR::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}

constexpr usart::RTOR::Data operator|(usart::RTOR::Data left_a, usart::RTOR::Data right_a)
{
    return static_cast<usart::RTOR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::RTOR::Data operator<<(xmcu::Limited<std::uint32_t, 0x0u, 0xFFFFFFu> value_a, usart_rtor_descriptor::Shift_rto)
{
    return static_cast<usart::RTOR::Data>(static_cast<std::uint32_t>(value_a));
}
constexpr usart::RTOR::Data operator<<(xmcu::Limited<std::uint32_t, 0x0u, 0xFFu> value_a, usart_rtor_descriptor::Shift_blen shift_a)
{
    return static_cast<usart::RTOR::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}

constexpr usart::RQR::Data operator|(usart_rqr_descriptor::Flag left_a, usart_rqr_descriptor::Flag right_a)
{
    return static_cast<usart::RQR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::RQR::Data operator|(usart::RQR::Data left_a, usart::RQR::Data right_a)
{
    return static_cast<usart::RQR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::RQR::Data operator|(usart_rqr_descriptor::Flag flag_a, usart::RQR::Data value_a)
{
    return static_cast<usart::RQR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::RQR::Data operator|(usart::RQR::Data value_a, usart_rqr_descriptor::Flag flag_a)
{
    return static_cast<usart::RQR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart_rqr_descriptor::Flag operator&(usart_rqr_descriptor::Flag flag_a, usart::RQR::Data value_a)
{
    return static_cast<usart_rqr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart_rqr_descriptor::Flag operator&(usart::RQR::Data value_a, usart_rqr_descriptor::Flag flag_a)
{
    return static_cast<usart_rqr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}

constexpr usart::ISR::Data operator|(usart_isr_descriptor::Flag left_a, usart_isr_descriptor::Flag right_a)
{
    return static_cast<usart::ISR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::ISR::Data operator|(usart::ISR::Data left_a, usart::ISR::Data right_a)
{
    return static_cast<usart::ISR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::ISR::Data operator|(usart_isr_descriptor::Flag flag_a, usart::ISR::Data value_a)
{
    return static_cast<usart::ISR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ISR::Data operator|(usart::ISR::Data value_a, usart_isr_descriptor::Flag flag_a)
{
    return static_cast<usart::ISR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ISR::Flag operator&(usart_isr_descriptor::Flag flag_a, usart::ISR::Data value_a)
{
    return static_cast<usart_isr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ISR::Flag operator&(usart::ISR::Data value_a, usart::ISR::Flag flag_a)
{
    return static_cast<usart_isr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ISR::Data operator&(usart::ISR::Data value_a, usart::ISR::Data flag_a)
{
    return static_cast<usart::ISR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ISR::Flag operator~(usart::ISR::Flag flag_a)
{
    return static_cast<usart::ISR::Flag>((~static_cast<std::uint32_t>(flag_a)));
}
constexpr usart::ISR::Data operator~(usart::ISR::Data flag_a)
{
    return static_cast<usart::ISR::Data>((~static_cast<std::uint32_t>(flag_a)));
}

constexpr usart::ICR::Data operator|(usart_icr_descriptor::Flag left_a, usart_icr_descriptor::Flag right_a)
{
    return static_cast<usart::ICR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::ICR::Data operator|(usart::ICR::Data left_a, usart::ICR::Data right_a)
{
    return static_cast<usart::ICR::Data>(static_cast<std::uint32_t>(left_a) | static_cast<std::uint32_t>(right_a));
}
constexpr usart::ICR::Data operator|(usart_icr_descriptor::Flag flag_a, usart::ICR::Data value_a)
{
    return static_cast<usart::ICR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ICR::Data operator|(usart::ICR::Data value_a, usart_icr_descriptor::Flag flag_a)
{
    return static_cast<usart::ICR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ICR::Flag operator&(usart_icr_descriptor::Flag flag_a, usart::ICR::Data value_a)
{
    return static_cast<usart_icr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ICR::Flag operator&(usart::ICR::Data value_a, usart_icr_descriptor::Flag flag_a)
{
    return static_cast<usart_icr_descriptor::Flag>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}
constexpr usart::ICR::Data operator&(usart::ICR::Data value_a, usart::ICR::Data flag_a)
{
    return static_cast<usart::ICR::Data>(static_cast<std::uint32_t>(flag_a) | static_cast<std::uint32_t>(value_a));
}

constexpr usart::PRESC::Data operator<<(usart_presc_descriptor::Mask value_a, usart_presc_descriptor::Shift_value shift_a)
{
    return static_cast<usart::PRESC::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
constexpr usart::PRESC::Data operator<<(usart_presc_descriptor::Value value_a, usart_presc_descriptor::Shift_value shift_a)
{
    return static_cast<usart::PRESC::Data>(static_cast<std::uint32_t>(value_a) << static_cast<std::uint32_t>(shift_a));
}
} // namespace soc::st::arm::m0::u0::rm0503::peripherals::ll