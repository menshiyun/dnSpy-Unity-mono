// 0 = .NET 2.0-3.5 Unity
// 1 = .NET 4.0+ Unity
#ifndef DNUNITYRT
#define DNUNITYRT 0
#endif

#ifndef DEFINED_LEGACY_PROFILER
#define MonoLegacyProfiler MonoProfiler
#endif

// dnSpy doesn't know which version this is so it will set both of these environment variables.
// Older dnSpy versions will only set the first one.
#define ENV_VAR_NAME_V0 "DNSPY_UNITY_DBG"
#define ENV_VAR_NAME_V1 "DNSPY_UNITY_DBG2"
#if DNUNITYRT == 0
#define ENV_VAR_NAME ENV_VAR_NAME_V0
#elif DNUNITYRT == 1
#define ENV_VAR_NAME ENV_VAR_NAME_V1
#else
#error Invalid DNUNITYRT value
#endif

extern gboolean dnSpy_hideDebugger = 1;

void
dnSpy_debugger_init ()
{
}

int
dnSpy_debugger_agent_parse_options (char* arg)
{
	if (strcmp (arg, "no-hide-debugger") == 0) {
		dnSpy_hideDebugger = 0;
		return 1;
	}

	return 0;
}

typedef struct { void* dummy; } DebuggerProfiler;
static DebuggerProfiler dnSpy_dummy_profiler;
static void
dnSpy_runtime_shutdown (MonoLegacyProfiler *prof)
{
}

void
dnSpy_debugger_init_after_agent ()
{
	// Prevent the debugger-agent's profiler events from being overwritten
	mono_profiler_install ((MonoLegacyProfiler*)&dnSpy_dummy_profiler, dnSpy_runtime_shutdown);
}
