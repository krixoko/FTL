/* Pi-hole: A black hole for Internet advertisements
*  (c) 2019 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  API routes
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */

#include "../FTL.h"
// struct mg_connection
#include "../civetweb/civetweb.h"
#include "../api/http-common.h"
#include "routes.h"

int api_handler(struct mg_connection *conn, void *ignored)
{
	const struct mg_request_info *request = mg_get_request_info(conn);
	// HTTP response
	int ret = 0;
	/******************************** api/dns ********************************/
	if(startsWith("/api/dns/status", request->local_uri))
	{
		ret = api_dns_status(conn);
	}
	else if(startsWith("/api/dns/whitelist/exact", request->local_uri))
	{
		ret = api_dns_somelist(conn, true, true);
	}
	else if(startsWith("/api/dns/whitelist/regex", request->local_uri))
	{
		ret = api_dns_somelist(conn, false, true);
	}
	else if(startsWith("/api/dns/blacklist/exact", request->local_uri))
	{
		ret = api_dns_somelist(conn, true, false);
	}
	else if(startsWith("/api/dns/blacklist/regex", request->local_uri))
	{
		ret = api_dns_somelist(conn, false, false);
	}
	/******************************** api/ftl ****************************/
	else if(startsWith("/api/ftl/clientIP", request->local_uri))
	{
		ret = api_ftl_clientIP(conn);
	}
	/******************************** api/stats **************************/
	else if(startsWith("/api/stats/summary", request->local_uri))
	{
		ret = api_stats_summary(conn);
	}
	else if(startsWith("/api/stats/overTime/history", request->local_uri))
	{
		ret = api_stats_overTime_history(conn);
	}
	else if(startsWith("/api/stats/overTime/clients", request->local_uri))
	{
		ret = api_stats_overTime_clients(conn);
	}
	else if(startsWith("/api/stats/query_types", request->local_uri))
	{
		ret = api_stats_query_types(conn);
	}
	else if(startsWith("/api/stats/upstreams", request->local_uri))
	{
		ret = api_stats_upstreams(conn);
	}
	else if(startsWith("/api/stats/top_domains", request->local_uri))
	{
		ret = api_stats_top_domains(false, conn);
	}
	else if(startsWith("/api/stats/top_blocked", request->local_uri))
	{
		ret = api_stats_top_domains(true, conn);
	}
	else if(startsWith("/api/stats/top_clients", request->local_uri))
	{
		ret = api_stats_top_clients(false, conn);
	}
	else if(startsWith("/api/stats/top_blocked_clients", request->local_uri))
	{
		ret = api_stats_top_clients(true, conn);
	}
	else if(startsWith("/api/stats/history", request->local_uri))
	{
		ret = api_stats_history(conn);
	}
	else if(startsWith("/api/stats/recent_blocked", request->local_uri))
	{
		ret = api_stats_recentblocked(conn);
	}
	/******************************** api/version ****************************/
	else if(startsWith("/api/version", request->local_uri))
	{
		ret = api_version(conn);
	}
	/******************************** api/auth ****************************/
	else if(startsWith("/api/auth", request->local_uri))
	{
		ret = api_auth(conn);
	}
	else if(startsWith("/api/auth/salt", request->local_uri))
	{
		ret = api_auth_salt(conn);
	}
	/******************************** api/settings ****************************/
	else if(startsWith("/api/settings/web", request->local_uri))
	{
		ret = api_settings_web(conn);
	}
	else if(startsWith("/api/settings/ftldb", request->local_uri))
	{
		ret = api_settings_ftldb(conn);
	}
	/******************************** not found ******************************/
/*	else
	{
		cJSON *json = JSON_NEW_OBJ();
		JSON_OBJ_REF_STR(json, "status", "requested path is not available");
		JSON_OBJ_REF_STR(json, "path", request->local_uri);
		JSON_SENT_OBJECT(json);
	}*/
	return ret;
}
