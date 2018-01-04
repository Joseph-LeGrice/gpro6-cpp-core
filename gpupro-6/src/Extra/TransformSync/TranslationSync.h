#pragma once

struct TranslationSync
{
    int m_transformId;
};

namespace TranslationSyncInternal
{
    struct InitTranslationSync
    {
        TranslationSync operator()()
        {
            TranslationSync t;
            t.m_transformId = -1;
            return t;
        }
    };
}

typedef ComponentRegistrationInfo<TranslationSync, 6, TranslationSyncInternal::InitTranslationSync> TranslationSyncComponent;
