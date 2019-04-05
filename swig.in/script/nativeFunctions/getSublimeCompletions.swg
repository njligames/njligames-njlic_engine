
    static std::string sublimeCompletions()
    {
        std::string output = "-- Automatically generated tests for ";
        output += SWIG_name;
        output += " game engine.\n\n";
        
        char trigger_value[512];
        char completion_value[512];
        
        std::string trigger0 = "\t\t{\"trigger\": \"";
        std::string trigger1 = "\", \"contents\": \"";
        std::string trigger2 = "\" },\n";
        
        //    std::string sublime_completions = "\n{\n\t\"scope\": \"source.lua -
        // source - meta.tag, punctuation.definition.tag.begin\",\n";
        //
        //    sublime_completions += "\n\n\t\"completions\":\n\t[\n";
        
        std::string sublime_completions = "";
        std::vector<std::string> sublime_completion_list;
        
        //this touches the SWIG internals, please be careful:
        for (int i = 0; swig_types[i]; i++)
        {
            if (swig_types[i]->clientdata)
            {
                swig_lua_class* ptr=(swig_lua_class*)(swig_types[i]->clientdata);
                
                // if (strcmp(name,ptr->name)==0)
                {
                    //                sprintf("test%sFunctions", ptr->name);
                    
                    for (int j = 0; ptr->cls_static->ns_constants[j].name; ++j)
                    {
                        
                        sprintf(trigger_value,
                        "%s",ptr->cls_static->ns_constants[j].name);
                        sprintf(completion_value,
                        "%s.%s", SWIG_name, ptr->cls_static->ns_constants[j].name);
                        
                        std::string completion("");
                        
                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;
                        
                        std::vector<std::string>::const_iterator iter =
                        std::find(sublime_completion_list.begin(),
                        sublime_completion_list.end(), completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }
                        
//                        sublime_completions += completions;

                    }
                    
                    for(int j = 0; ptr->cls_static->ns_methods[j].name; ++j)
                    {
                        sprintf(trigger_value, "static %s.%s",ptr->name,ptr->cls_static->ns_methods[j].name);
                        sprintf(completion_value,
                        "%s.%s.%s", SWIG_name, ptr->name,ptr->cls_static->ns_methods[j].name);
                        
                        std::string completion("");
                        
                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;
                        
                        std::vector<std::string>::const_iterator iter =
                        std::find(sublime_completion_list.begin(),
                        sublime_completion_list.end(), completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }
                        
//                        sublime_completions += completions;
                    }
                    
                    for(int j = 0; ptr->metatable[j].name; ++j)
                    {
//                        if(strcmp("Node", ptr->name) == 0)
//                        {
//                            printf("%s:%s\n",ptr->name,ptr->metatable[j].name);
//                        }
                    }
                    for(int j = 0; ptr->methods[j].name; ++j)
                    {
//                        if(strcmp("Node", ptr->name) == 0)
//                        {
//                            printf("%s:%s\n",ptr->name,ptr->methods[j].name);
//
//                            printf("%s:%s\n",ptr->name,ptr->methods[j].name);
//                        }
                    }
                    
                    for(int j = 0; ptr->methods[j].name; ++j)
                    {
//                        if(strcmp("Node", ptr->name) == 0)
//                        {
//                            //                        swig_lua_method method = ptr->methods[j];
//                            sprintf(trigger_value,
//                            "%s.%s",ptr->name,ptr->methods[j].name);
//                            sprintf(completion_value, "%s",ptr->methods[j].name);
//                        }
                        
                        sprintf(trigger_value,
                        "%s.%s",ptr->name,ptr->methods[j].name);
                        sprintf(completion_value, "%s",ptr->methods[j].name);
                        
                        std::string completion("");
                        
                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;
                        
                        std::vector<std::string>::const_iterator iter =
                        std::find(sublime_completion_list.begin(),
                        sublime_completion_list.end(), completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }
                        
//                        sublime_completions += completions;
                    }
                    
                    //                for(int j=0;ptr->methods[j].name;j++)
                    //                {
                    //                    sprintf(buffer,
                    //"%s::%s()\n",ptr->name,ptr->methods[j].name);
                    ////                    functions += buffer;
                    // SDL_LogVerbose(SDL_LOG_CATEGORY_TEST,
                    //"%s::%s()\n",ptr->name,ptr->methods[j].name);
                    //                }
                }
            }
        }
        //    sublime_completions += "\t]\n}";
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s",sublime_completions.c_str());
        
        for(std::vector<std::string>::const_iterator iter = sublime_completion_list.begin();
        iter != sublime_completion_list.end();
        iter++)
        {
            sublime_completions += *iter;
        }
        return sublime_completions;
        //    Log("%s", functions.c_str());
    }
    
    int getSublimeCompletions(lua_State*L) // my native code
    {
        lua_pushstring(L, sublimeCompletions().c_str());
        return 1;
    }
