            static consteval auto name()
            {
#if __clang__
                std::string_view sv = __PRETTY_FUNCTION__; // static auto A::name
                sv = sv.substr(sizeof("static auto ") - 1);
#elif __GNUC__
                std::string_view sv = __PRETTY_FUNCTION__; // static constexpr auto A::name
                sv = sv.substr(sizeof("static constexpr auto ") - 1);
#elif _MSC_VER
                std::string_view sv = __FUNCSIG__; // A::name
                if (sv.starts_with("auto __cdecl ")) // Visual Studio 2022: auto __cdecl A::name
                {
                    sv = sv.substr(sizeof("auto __cdecl ") - 1);
                }
#endif
                return sv.substr(0, sv.rfind("::name"));
            }