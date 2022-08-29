#include "Facts.h"

// ----------------------------------- Facts -------------------------------------

void AddFact(SordModel* mod, char* s, char* p, char* o, char* g)
{
    SordWorld* world = sord_get_world(mod);
    SordNode* subject = sord_new_uri(world, (const uint8_t*)s);
    SordNode* predicate = sord_new_uri(world, (const uint8_t*)p);
    SordNode* object = sord_new_uri(world, (const uint8_t*)o);
    SordNode* graph = sord_new_uri(world, (const uint8_t*)g);
    SordQuad quad = {subject, predicate, object, graph};

    if (!sord_ask(mod, subject, predicate, object, graph))
    {
        sord_add(mod, quad);
    }

    sord_node_free(world, subject);
    sord_node_free(world, predicate);
    sord_node_free(world, object);
    sord_node_free(world, graph);

}

void AddFactWithLiteralObject(SordModel* mod, char* s, char* p, char* o, char* g, char* datatype)
{
    SordWorld* world = sord_get_world(mod);
    SordNode* subject = sord_new_uri(world, (const uint8_t*)s);
    SordNode* predicate = sord_new_uri(world, (const uint8_t*)p);

    SordNode* datatypeNode = sord_new_uri(world, (const uint8_t*)datatype);
    SordNode* object = sord_new_literal(world, datatypeNode, (const uint8_t*)o, NULL);

    SordNode* graph = sord_new_uri(world, (const uint8_t*)g);
    SordQuad quad = {subject, predicate, object, graph};

    if (!sord_ask(mod, subject, predicate, object, graph))
    {
        sord_add(mod, quad);
    }

    sord_node_free(world, subject);
    sord_node_free(world, predicate);
    sord_node_free(world, object);
    sord_node_free(world, datatypeNode);
    sord_node_free(world, graph);
}

void AddFactsFromObservation(SordModel* mod, Observation* obs)
{
    //get the graph
    char graph[50] = "http://example.org/graph/g1";

    //get the subject from the observation
    char* subject = getSubject(obs);

    //Differents predicats and associated objects
    char P_SensorType[50] = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
    char* O_SensorType = getObject(obs,P_SensorType);

    char P_MoreSensorType[50] = "http://www.w3.org/ns/sosa/observedProperty";
    char* O_MoreSensorType = getObject(obs, P_MoreSensorType);
    

    char P_DateTime[50] = "http://www.w3.org/ns/sosa/phenomenonTime";
    char* O_DateTime = getObject(obs,P_DateTime);

    char P_MoreDateTime[50] = "http://www.w3.org/ns/sosa/resultTime";
    char* O_MoreDateTime = getObject(obs,P_MoreDateTime);
    

    char P_Other[50] = "http://www.w3.org/ns/sosa/madeBySensor";
    char* O_Other = getObject(obs,P_Other);

    char P_ObservedValue[50] = "http://www.w3.org/ns/sosa/hasSimpleResult";
    char* O_ObservedValue = getObject(obs,P_ObservedValue);

    
    //Add facts
    AddFact(mod,subject, P_SensorType, O_SensorType, graph);
    AddFact(mod,subject, P_MoreSensorType, O_MoreSensorType, graph);
    AddFact(mod,subject, P_DateTime, O_DateTime, graph);
    AddFact(mod,subject, P_Other, O_Other, graph);
    

    //create a datatype (as a string) for the literal node (object) of observed value
    char strDatatypeObservedValue[] = "xsd:float";

    AddFactWithLiteralObject(mod,subject, P_ObservedValue, O_ObservedValue, graph, strDatatypeObservedValue);

    //create a datatype (as a string) for the literal node (object) of Date and time
    char strDatatypeMoreDateTime[] = "xsd:dateTime";

    AddFactWithLiteralObject(mod,subject, P_MoreDateTime, O_MoreDateTime, graph, strDatatypeMoreDateTime);
    
    free(subject);
    free(O_SensorType); 
    free(O_MoreSensorType);
    free(O_DateTime);
    free(O_MoreDateTime);
    free(O_Other);
    free(O_ObservedValue);
}

void AddFactsFromLinkedList(LinkedList* l, SordModel* mod)
{
    
	LinkedListNode* curr = l->first;
	while (curr != NULL)
	{
        AddFactsFromObservation(mod,curr->data);
		curr = curr->next;
	}
}

void makeFileFacts(char* filepath, SordModel* mod)
{
    FILE *file = NULL;
    file = fopen(filepath, "w");
    if(file!= NULL)
    {
        SordWorld* world = sord_get_world(mod);
        SerdEnv* env = serd_env_new(NULL);
        SerdWriter* writer = serd_writer_new(SERD_TURTLE, SERD_STYLE_ABBREVIATED, env, NULL, serd_file_sink, file);

        //Put the prefixes name and prefixes URI in the file
        char* prefixNameStr = calloc(10, sizeof(char));
        strcpy(prefixNameStr, "rdfs");
        SordNode* prefixName = createSordNodeLiteral(prefixNameStr,mod);

        char* prefixUriStr = calloc(50, sizeof(char));
        strcpy(prefixUriStr, "http://www.w3.org/2000/01/rdf-schema#");
        SordNode* prefixURI = createSordNode(prefixUriStr,mod);

        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "xsd");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://www.w3.org/2001/XMLSchema#");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "time");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://www.w3.org/2006/time#");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "ont");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "https://coswot.gitlab.io/ontology#");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "sos");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://www.w3.org/ns/sosa/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "s");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/sample/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "res");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/result/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "cdt");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "https://w3id.org/cdt/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "sen");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/sensor/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "pro");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/property/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "pl");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/platform/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "qudt");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://qudt.org/schema/qudt/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "unit");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://qudt.org/vocab/unit/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "room");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/room/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "bot");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "https://w3id.org/bot#");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "sto");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/storey/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "ssn");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://www.w3.org/ns/ssn/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "bui");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://example.org/id/building/");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        strcpy(prefixNameStr, "rdf");
        prefixName = createSordNodeLiteral(prefixNameStr,mod);
        strcpy(prefixUriStr, "http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
        prefixURI = createSordNode(prefixUriStr,mod);
        serd_writer_set_prefix(writer, sord_node_to_serd_node(prefixName), sord_node_to_serd_node(prefixURI));

        SordIter* tempFacts = sord_begin(mod);
        while (!sord_iter_end(tempFacts))
        {
            SordQuad quad;
            sord_iter_get(tempFacts, quad);

            SordNode* datatype = sord_node_get_datatype(quad[2]);

            serd_writer_write_statement(writer, 0, sord_node_to_serd_node(quad[3]), sord_node_to_serd_node(quad[0]), sord_node_to_serd_node(quad[1]), sord_node_to_serd_node(quad[2]), sord_node_to_serd_node(datatype), NULL);
            sord_iter_next(tempFacts);
        }
        serd_writer_finish(writer);

        sord_iter_free(tempFacts);
        serd_writer_free(writer);
        serd_env_free(env);

        free(prefixNameStr);
        free(prefixUriStr);
        sord_node_free(world,prefixName);
        sord_node_free(world,prefixURI);

        fclose(file);
    }
    else
    {
        printf("Cannot open file");
    }
}


void printFact(SordModel* mod)
{
    SerdEnv* env = serd_env_new(NULL);
    SerdChunk chunk = {NULL, 0};
    SerdWriter* writer = serd_writer_new(SERD_TURTLE, SERD_STYLE_ABBREVIATED, env, NULL, serd_chunk_sink, &chunk);

    SordIter* tempFacts = sord_begin(mod);
    int count = 0;
    while (!sord_iter_end(tempFacts))
    {
        SordQuad quad;
        sord_iter_get(tempFacts, quad);

        SordNode* datatype = sord_node_get_datatype(quad[2]);

        serd_writer_write_statement(writer, 0, sord_node_to_serd_node(quad[3]), sord_node_to_serd_node(quad[0]), sord_node_to_serd_node(quad[1]), sord_node_to_serd_node(quad[2]), sord_node_to_serd_node(datatype), NULL);
        sord_iter_next(tempFacts);
        count++;
    }
    sord_iter_free(tempFacts);
    serd_writer_free(writer);
    serd_env_free(env);
    char* out = (char*)serd_chunk_sink_finish(&chunk);

    printf("\n\n*************************print of differents facts :******************************\n\n");
    printf("%s\n", out);

    printf("%d facts read from the model\n", count);

    //Free the string of facts
    free(out);
}

void readFileOfFacts(char* initialFactFilePath)
{
        SordWorld* world = sord_world_new();
        SordModel* kb = sord_new(world, SORD_SPO, false);

        if (initialFactFilePath != NULL)
        {
            SerdEnv* env = serd_env_new(NULL);
            SerdReader* reader = sord_new_reader(kb, env, SERD_TURTLE, NULL);

            FILE* file = fopen(initialFactFilePath, "r");
            SerdStatus status = serd_reader_read_file_handle(reader, file, NULL);
            if (status == SERD_SUCCESS)
            {
                fclose(file);
                serd_env_free(env);
                serd_reader_free(reader);
                printf("-----> %zu facts read in the file facts.ttl.\n", sord_num_quads(kb));
            }
            else
            {
                fclose(file);
                serd_env_free(env);
                serd_reader_free(reader);
            }
        }
}

SordNode* createSordNode(char* str, SordModel* mod)
{
    SordWorld* world = sord_get_world(mod);
    SordNode* sordnode = sord_new_uri(world, (const uint8_t*)str);

    return sordnode;
}

SordNode* createSordNodeLiteral(char* str, SordModel* mod)
{
    SordWorld* world = sord_get_world(mod);
    SordNode* sordnode = sord_new_literal(world, NULL, (const uint8_t*)str, NULL);

    return sordnode;
}
