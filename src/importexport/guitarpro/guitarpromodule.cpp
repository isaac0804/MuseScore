/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "guitarpromodule.h"

#include "modularity/ioc.h"

#include "project/inotationreadersregister.h"
#include "internal/guitarproreader.h"

#ifndef IEX_GUITARPRO_NO_INTERNAL
#include "internal/guitarproconfiguration.h"
#endif

#include "log.h"

using namespace mu::iex::guitarpro;
using namespace mu::project;

#ifndef IEX_GUITARPRO_NO_INTERNAL
static std::shared_ptr<GuitarProConfiguration> s_configuration = std::make_shared<GuitarProConfiguration>();
#endif

std::string GuitarProModule::moduleName() const
{
    return "iex_guitarpro";
}

void GuitarProModule::registerExports()
{
#ifndef IEX_GUITARPRO_NO_INTERNAL
    modularity::ioc()->registerExport<IGuitarProConfiguration>(moduleName(), s_configuration);
#endif
}

void GuitarProModule::resolveImports()
{
    auto readers = modularity::ioc()->resolve<INotationReadersRegister>(moduleName());
    if (readers) {
        readers->reg({ "gtp", "gp3", "gp4", "gp5", "gpx", "gp", "ptb" }, std::make_shared<GuitarProReader>());
    }
}

void GuitarProModule::onInit(const framework::IApplication::RunMode&)
{
#ifndef IEX_GUITARPRO_NO_INTERNAL
    s_configuration->init();
#endif
}
