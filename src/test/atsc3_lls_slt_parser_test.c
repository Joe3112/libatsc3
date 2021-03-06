/*
 *
 * atsc3_lls_slt_parser_test.c
 *
 *
 *
<?xml version="1.0" encoding="UTF-8"?>
<SLT xmlns="tag:atsc.org,2016:XMLSchemas/ATSC3/Delivery/SLT/1.0/" bsid="50">
   <Service serviceId="1001" globalServiceID="urn:atsc:serviceid:ateme_mmt_1" majorChannelNo="10" minorChannelNo="1" serviceCategory="1" shortServiceName="ATEME MMT 1" sltSvcSeqNum="0">
      <BroadcastSvcSignaling slsProtocol="2" slsDestinationIpAddress="239.255.10.1" slsDestinationUdpPort="51001" slsSourceIpAddress="172.16.200.1" />
   </Service>
   <Service serviceId="1002" globalServiceID="urn:atsc:serviceid:ateme_mmt_2" majorChannelNo="10" minorChannelNo="2" serviceCategory="1" shortServiceName="ATEME MMT 2" sltSvcSeqNum="0">
      <BroadcastSvcSignaling slsProtocol="2" slsDestinationIpAddress="239.255.10.2" slsDestinationUdpPort="51002" slsSourceIpAddress="172.16.200.1" />
   </Service>
   <Service serviceId="1003" globalServiceID="urn:atsc:serviceid:ateme_mmt_3" majorChannelNo="10" minorChannelNo="3" serviceCategory="1" shortServiceName="ATEME MMT 3" sltSvcSeqNum="0">
      <BroadcastSvcSignaling slsProtocol="2" slsDestinationIpAddress="239.255.10.3" slsDestinationUdpPort="51003" slsSourceIpAddress="172.16.200.1" />
   </Service>
   <Service serviceId="1004" globalServiceID="urn:atsc:serviceid:ateme_mmt_4" majorChannelNo="10" minorChannelNo="4" serviceCategory="1" shortServiceName="ATEME MMT 4" sltSvcSeqNum="0">
      <BroadcastSvcSignaling slsProtocol="2" slsDestinationIpAddress="239.255.10.4" slsDestinationUdpPort="51004" slsSourceIpAddress="172.16.200.1" />
   </Service>
   <Service serviceId="5009" globalServiceID="urn:atsc:serviceid:esg" serviceCategory="4" shortServiceName="ESG" sltSvcSeqNum="0">
      <BroadcastSvcSignaling slsProtocol="1" slsDestinationIpAddress="239.255.20.9" slsDestinationUdpPort="52009" slsSourceIpAddress="172.16.200.1" />
   </Service>
</SLT>
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../atsc3_lls.h"

#define __UNIT_TEST 1
#ifdef __UNIT_TEST

extern int _LLS_DEBUG_ENABLED;

void test_parse_xml(char* xml);

char* test_slt_table = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><SLT xmlns=\"tag:atsc.org,2016:XMLSchemas/ATSC3/Delivery/SLT/1.0/\" bsid=\"50\"><Service serviceId=\"1001\" globalServiceID=\"urn:atsc:serviceid:ateme_mmt_1\" majorChannelNo=\"10\" minorChannelNo=\"1\" serviceCategory=\"1\" shortServiceName=\"ATEME MMT 1\" sltSvcSeqNum=\"0\"><BroadcastSvcSignaling slsProtocol=\"2\" slsDestinationIpAddress=\"239.255.10.1\" slsDestinationUdpPort=\"51001\" slsSourceIpAddress=\"172.16.200.1\"/></Service><Service serviceId=\"1002\" globalServiceID=\"urn:atsc:serviceid:ateme_mmt_2\" majorChannelNo=\"10\" minorChannelNo=\"2\" serviceCategory=\"1\" shortServiceName=\"ATEME MMT 2\" sltSvcSeqNum=\"0\"><BroadcastSvcSignaling slsProtocol=\"2\" slsDestinationIpAddress=\"239.255.10.2\" slsDestinationUdpPort=\"51002\" slsSourceIpAddress=\"172.16.200.1\"/></Service><Service serviceId=\"1003\" globalServiceID=\"urn:atsc:serviceid:ateme_mmt_3\" majorChannelNo=\"10\" minorChannelNo=\"3\" serviceCategory=\"1\" shortServiceName=\"ATEME MMT 3\" sltSvcSeqNum=\"0\"><BroadcastSvcSignaling slsProtocol=\"2\" slsDestinationIpAddress=\"239.255.10.3\" slsDestinationUdpPort=\"51003\" slsSourceIpAddress=\"172.16.200.1\"/></Service><Service serviceId=\"1004\" globalServiceID=\"urn:atsc:serviceid:ateme_mmt_4\" majorChannelNo=\"10\" minorChannelNo=\"4\" serviceCategory=\"1\" shortServiceName=\"ATEME MMT 4\" sltSvcSeqNum=\"0\"><BroadcastSvcSignaling slsProtocol=\"2\" slsDestinationIpAddress=\"239.255.10.4\" slsDestinationUdpPort=\"51004\" slsSourceIpAddress=\"172.16.200.1\"/></Service><Service serviceId=\"5009\" globalServiceID=\"urn:atsc:serviceid:esg\" serviceCategory=\"4\" shortServiceName=\"ESG\" sltSvcSeqNum=\"0\"><BroadcastSvcSignaling slsProtocol=\"1\" slsDestinationIpAddress=\"239.255.20.9\" slsDestinationUdpPort=\"52009\" slsSourceIpAddress=\"172.16.200.1\"/></Service></SLT>";


int main() {

	test_parse_xml(test_slt_table);

	return 0;
}

void test_parse_xml(char* xml) {

	_LLS_DEBUG("parsing: %s", xml);
	struct xml_document* document = xml_parse_document((uint8_t*)xml, strlen(xml));
	if (!document) {
			printf("Could not parse document\n");
			exit(EXIT_FAILURE);
	}
	struct xml_node* root = xml_document_root(document);
	printf("-----%d:xml_easy_child\n", __LINE__);

	struct xml_node *node = xml_node_child(root, 0); //"SLT");
	printf("SLT node: %p", node);

	struct xml_string* node_name = xml_node_name(node);
	dump_xml_string(node_name);

	int child_size = xml_node_children(node);
	for(int i=0; i < child_size; i++) {
		struct xml_node* svc_row = xml_node_child(node, i);
		struct xml_string* svc_row_name = xml_node_name(svc_row);
		dump_xml_string(svc_row_name);

		if(xml_node_children(svc_row)) {
			struct xml_node* bss = xml_node_child(svc_row, 0);
			struct xml_string* bss_row_name = xml_node_name(bss);

			dump_xml_string(bss_row_name);
		}
	}
}

#endif


