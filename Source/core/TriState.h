#ifndef __TRISTATE_H
#define __TRISTATE_H

#include "Module.h"
#include "Optional.h"

namespace WPEFramework {
namespace Core {

    class TriState {
    public:
        enum EnumState {
            True,
            False,
            Unknown
        };

    public:
        TriState()
            : m_State(Unknown)
        {
        }
        explicit TriState(const TCHAR* text, const uint32_t length = NUMBER_MAX_UNSIGNED(uint32_t))
            : m_State(Unknown)
        {
            // Time to see if there is a value
            if ((length == 1) || (text[1] == '\0')) {
                // Its a single character flag, t/T or f/F
                if (toupper(text[0]) == 'F') {
                    m_State = False;
                }
                else if (toupper(text[0]) == 'T') {
                    m_State = True;
                }
            }
            else if ((length == 4) || (toupper(text[4]) == '\0')) {
                uint8_t index = 0;
                TCHAR value[] = _T("TRUE\0");

                while ((index < 4) && (toupper(text[index]) == value[index])) {
                    index++;
                }

                if (index == 4) {
                    m_State = True;
                }
            }
            else if ((length == 5) || (toupper(text[5]) == '\0')) {
                uint8_t index = 0;
                TCHAR value[] = _T("FALSE\0");

                while ((index < 5) && (toupper(text[index]) == value[index])) {
                    index++;
                }

                if (index == 5) {
                    m_State = False;
                }
            }
        }
        explicit TriState(EnumState state)
            : m_State(state)
        {
        }
        TriState(const TriState& copy)
            : m_State(copy.m_State)
        {
        }
        ~TriState()
        {
        }

        TriState& operator=(const TriState& rhs)
        {
            m_State = rhs.m_State;
            return (*this);
        }

    public:
        inline TriState& operator=(const bool rhs)
        {
            m_State = rhs ? True : False;
            return (*this);
        }
        inline TriState& operator=(const EnumState rhs)
        {
            m_State = rhs;
            return (*this);
        }
        inline bool operator==(bool other) const
        {
            return (other == true && m_State == True) || (other == false && m_State == False);
        }
        inline bool operator!=(bool other) const
        {
            return (!operator==(other));
        }
        operator OptionalType<bool>()
        {
            return (m_State == Unknown ? OptionalType<bool>() : OptionalType<bool>(m_State == True));
        }
        inline EnumState Get() const
        {
            return (m_State);
        }

        // Set returns TRUE if changed
        inline bool Set(bool value)
        {
            EnumState oldState = m_State;
            m_State = value ? True : False;
            return m_State != oldState;
        }

        // Set returns TRUE if changed
        inline bool Set(EnumState value)
        {
            EnumState oldState = m_State;
            m_State = value;
            return m_State != oldState;
        }

    private:
        EnumState m_State;
    };
}
} // namespace Core

#endif // __TRISTATE_H
