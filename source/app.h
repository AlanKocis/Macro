#pragma once
#include "FileManager.h"
#include "Day.h"
#include "Entry.h"
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <iterator>
#include <cstdio>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace app
{
	GLFWwindow *window;
	bool is_running = true;
	const int INIT_HEIGHT = 500, INIT_WIDTH = 400;
	std::string todays_date_global = "";
	FileManager& fileManager = FileManager::instance();
	 
	std::vector<Day> days;
	
	void init()
	{
//		boilerplate
		glfwInit();

		window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "Macro Log", NULL, NULL);
		if (!window)
		{
			printf("Couldn't create GLFW window\n");
			glfwTerminate();
			exit(-1);
		}

		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "GLAD failed\n";
			exit(-1);
		}


		fileManager.init_buffers(days);

//		get user's local day as string
		time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm time_data = *std::localtime(&current_time);
		std::stringstream ss;
		ss << std::put_time(&time_data, "%m%d%Y");
		std::string todays_date;
		ss >> todays_date;
		
		todays_date_global = todays_date;


//		check end of buffer only to test if application has been opened today
		auto it = days.rbegin();
		if (!(it->date == todays_date))
		{
			days.emplace_back(Day(todays_date));
		}

//		init imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		printf("finished initializing.\n");
	}

	void update_gui()
	{
		int WIDTH = 0, HEIGHT = 0;
		glfwGetWindowSize(window, &WIDTH, &HEIGHT);
		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		//		FIRST WINDOW BEGIN
		ImGui::Begin("1", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		static ImVec4 color(1, 0, 0, 1);

		auto it = days.rbegin();
		std::string appText = std::to_string(it->get_total_calories()) + " Kilocalories eaten";
		std::string appText2 = std::to_string(it->get_total_protein()) + "g Protein eaten";

		ImGui::TextColored(color, todays_date_global.c_str());
		ImGui::Text(appText.c_str());
		ImGui::Text(appText2.c_str());



		static int item_current_idx = 0;
		if (ImGui::BeginListBox("1", ImVec2(200, 100)))
		{
			for (int i = 0; i < it->entries.size(); i++)
			{
				const bool is_selected = (item_current_idx == i);
				std::string s = it->entries[i].get_name();
				if (ImGui::Selectable(it->entries[i].get_name().c_str()), is_selected)
				{
					item_current_idx = i;

//					___________________________________________________________________________________________________
//					TODO::HIGH PRIORITY 
//					ImGui::Selectable won't actually select because of .c_str() every frame (new address)
//					___________________________________________________________________________________________________
//					todo:	switch Entry.h from using an std::string to a char[] for its name string so we can just
// 							use that as the object's ID instead of calling .c_str() every frame.
// 					___________________________________________________________________________________________________
				}

			}
		

			ImGui::EndListBox();
		}





		static bool gate = false;

		if (!gate && ImGui::Button("Add Entry", ImVec2(90, 40))) { gate = true; }

		if (gate)
		{
			ImGui::PushItemWidth(152);
			static char name_str[64] = "enter name\0";
			name_str[63] = '\0';
			ImGui::Text("Name:");		ImGui::SameLine();	ImGui::InputText("##NameInput", name_str, IM_ARRAYSIZE(name_str));
			for (int i = 0; i < 63; i++)
			{
				if (name_str[i] == ' ')
					name_str[i] = '_';
			}
			ImGui::PopItemWidth();


			ImGui::PushItemWidth(64);
			static float kcal = 0.0F;

			ImGui::Text("Kcal:");
			ImGui::SameLine();
			ImGui::PushItemWidth(40);
			ImGui::InputFloat("##KcalInput", &kcal, 0.0F, 0.0F, "%.2f", 0);
			ImGui::PopItemWidth();

			static float protein = 0.0F;
			ImGui::SameLine();	ImGui::Text("Protein:");
			ImGui::PushItemWidth(40);
			ImGui::SameLine();	ImGui::InputFloat("##ProteinInput", &protein, 0.0F, 0.0F, "%.2f", 0);
			ImGui::PopItemWidth();

			static float servings = 1.0F;
			ImGui::PushItemWidth(30);
			ImGui::InputFloat("servings", &servings, 0.0F, 0.0F, "%.1f", 0);
			ImGui::PopItemWidth();


			if (ImGui::Button("Add", ImVec2(80, 30)))
			{
				auto it = days.rbegin();
				std::string str = name_str;
				Entry food(str, kcal, protein, servings);
				it->push_entry(food);
				gate = false;
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(80, 30))) { gate = false; }



		}


//		FIRST WINDOW END
		ImGui::End();
//


		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2));
		ImGui::SetNextWindowPos(ImVec2(0, HEIGHT / 2));

//		SECOND WINDOW BEGIN
		ImGui::Begin("2", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//

		for (Day &day : days)
		{
			if (ImGui::TreeNode(day.date.c_str()))
			{
				for (Entry &food : day.entries)
				{

					ImGui::Text(food.get_name().c_str());
					static char foodStr[64];

				}
				ImGui::TreePop();
			}
		}



//		SECOND WINDOW END
		ImGui::End();


	}

	void run()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); 
		ImGui::NewFrame();


		update_gui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			is_running = false;
	}
}