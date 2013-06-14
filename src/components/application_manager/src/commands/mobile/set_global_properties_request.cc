/*

 Copyright (c) 2013, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/commands/mobile/set_global_properties_request.h"
#include "application_manager/application_manager_impl.h"
#include "application_manager/application_impl.h"
#include "application_manager/message_chaining.h"
#include "JSONHandler/SDLRPCObjects/V2/HMILevel.h"
#include "utils/logger.h"

namespace application_manager {

namespace commands {

log4cxx::LoggerPtr logger_ =
  log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Commands"));

SetGlobalPropertiesRequest::SetGlobalPropertiesRequest(
    const MessageSharedPtr& message): CommandRequestImpl(message) {
}

SetGlobalPropertiesRequest::~SetGlobalPropertiesRequest() {
}

void SetGlobalPropertiesRequest::Run() {
  LOG4CXX_INFO(logger_, "SetGlobalPropertiesRequest::Run ");

  ApplicationImpl* app = static_cast<ApplicationImpl*>(
      ApplicationManagerImpl::instance()->
      application((*message_)[strings::params][strings::connection_key]));

  if (NULL == app) {
    LOG4CXX_ERROR_EXT(logger_, "No application associated with session key ");
    SendResponse(false,
                 NsSmartDeviceLinkRPC::V2::Result::APPLICATION_NOT_REGISTERED);
    return;
  }

  app->set_help_prompt(
      (*message_)[strings::msg_params][strings::help_promt]);
  app->set_timeout_prompt(
      (*message_)[strings::msg_params][strings::timeout_promt]);
  app->set_vr_help_title(
      (*message_)[strings::msg_params][strings::vr_help_title]);
  app->set_vr_help(
      (*message_)[strings::msg_params][strings::vr_help]);

  const int correlation_id =
      (*message_)[strings::params][strings::correlation_id];
  const int connection_key =
      (*message_)[strings::params][strings::connection_key];

  const unsigned int cmd_id = 14;
  ApplicationManagerImpl::instance()->AddMessageChain(
      new MessageChaining(connection_key, correlation_id),
      connection_key, correlation_id, cmd_id);

  smart_objects::CSmartObject* p_smrt_ui  = new smart_objects::CSmartObject();

  // TODO(DK) HMI Request Id
  const int ui_cmd_id = 1;
  (*p_smrt_ui)[strings::params][strings::function_id] =
      ui_cmd_id;

  (*p_smrt_ui)[strings::params][strings::message_type] =
      MessageType::kRequest;

  (*p_smrt_ui)[strings::msg_params][strings::cmd_id] =
      (*message_)[strings::msg_params][strings::cmd_id];

  (*p_smrt_ui)[strings::msg_params][strings::vr_help_title] =
      app->vr_help_title();

  (*p_smrt_ui)[strings::msg_params][strings::vr_help] =
      app->vr_help();

  (*p_smrt_ui)[strings::msg_params][strings::app_id] =
      app->app_id();
  ApplicationManagerImpl::instance()->SendMessageToHMI(p_smrt_ui);
}

}  // namespace commands

}  // namespace application_manager