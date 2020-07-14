/***************************************************************************
 *   This file is part of Webbino                                          *
 *                                                                         *
 *   Copyright (C) 2012-2019 by SukkoPera                                  *
 *                                                                         *
 *   Webbino is free software: you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Webbino is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with Webbino. If not, see <http://www.gnu.org/licenses/>.       *
 ***************************************************************************/

#ifndef _HTTPREQUESTPARSER_H_
#define _HTTPREQUESTPARSER_H_

#include <webbino_config.h>
#include <webbino_debug.h>


class HTTPRequestParser {
public:
	static const byte MAX_MATCHES = 4;

	struct MatchResult {
		byte matchPositions[MAX_MATCHES];
		byte matchLengths[MAX_MATCHES];
		byte nMatches;
	};

	enum HttpMethod {
		METHOD_GET,
		METHOD_PUT,
		METHOD_POST,
		METHOD_DELETE,
		METHOD_UNKNOWN		// Keep at end, not supported ATM
	};

	MatchResult matchResult;

	HttpMethod method;

#ifdef ENABLE_HTTPAUTH
	const char *username;
	const char *password;
#endif

	HTTPRequestParser ();

	char uri[MAX_URL_LEN];

	boolean parse (const char *request);

	char *get_basename ();

	char *get_parameter (const char param[]);

#ifdef ENABLE_FLASH_STRINGS
	char *get_parameter (WebbinoFStr param);
#endif

	boolean matchAssociation (const char *assocPath);

private:
	char buffer[BUF_LEN];

#ifdef ENABLE_HTTPAUTH
	char userpassBuf [MAX_USERPASS_LEN + 2];	// Add 2 for separator and terminator
#endif

	static boolean parametricMatch (const char *str, const char *expr, MatchResult& result);
};

#endif
