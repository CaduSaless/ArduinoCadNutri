# ArduinoCadNutri

Traceback (most recent call last):
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 1536, in __call__
    return self.wsgi_app(environ, start_response)
           ~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask_socketio/__init__.py", line 42, in __call__
    return super().__call__(environ, start_response)
           ~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/engineio/middleware.py", line 74, in __call__
    return self.wsgi_app(environ, start_response)
           ~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 1514, in wsgi_app
    response = self.handle_exception(e)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask_cors/extension.py", line 176, in wrapped_function
    return cors_after_request(app.make_response(f(*args, **kwargs)))
                                                ~^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 1511, in wsgi_app
    response = self.full_dispatch_request()
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 919, in full_dispatch_request
    rv = self.handle_user_exception(e)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask_cors/extension.py", line 176, in wrapped_function
    return cors_after_request(app.make_response(f(*args, **kwargs)))
                                                ~^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 917, in full_dispatch_request
    rv = self.dispatch_request()
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/flask/app.py", line 902, in dispatch_request
    return self.ensure_sync(self.view_functions[rule.endpoint])(**view_args)  # type: ignore[no-any-return]
           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/routes/peso.py", line 78, in medir_peso
    resposta = client.models.generate_content(
    
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/models.py", line 5709, in generate_content
    response = self._generate_content(
    
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/models.py", line 4371, in _generate_content
    response = self._api_client.request(
    
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/_api_client.py", line 1401, in request
    response = self._request(http_request, http_options, stream=False)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/_api_client.py", line 1237, in _request
    return self._retry(self._request_once, http_request, stream)  # type: ignore[no-any-return]
           ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/tenacity/__init__.py", line 470, in __call__
    do = self.iter(retry_state=retry_state)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/tenacity/__init__.py", line 371, in iter
    result = action(retry_state)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/tenacity/__init__.py", line 413, in exc_check
    raise retry_exc.reraise()
          ~~~~~~~~~~~~~~~~~^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/tenacity/__init__.py", line 184, in reraise
    raise self.last_attempt.result()
          ~~~~~~~~~~~~~~~~~~~~~~~~^^
  File "/opt/homebrew/Cellar/python@3.14/3.14.3/Frameworks/Python.framework/Versions/3.14/lib/python3.14/concurrent/futures/_base.py", line 443, in result
    return self.__get_result()
           ~~~~~~~~~~~~~~~~~^^
  File "/opt/homebrew/Cellar/python@3.14/3.14.3/Frameworks/Python.framework/Versions/3.14/lib/python3.14/concurrent/futures/_base.py", line 395, in __get_result
    raise self._exception
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/tenacity/__init__.py", line 473, in __call__
    result = fn(*args, **kwargs)
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/_api_client.py", line 1214, in _request_once
    errors.APIError.raise_for_response(response)
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/errors.py", line 134, in raise_for_response
    cls.raise_error(response.status_code, response_json, response)
    ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/profabrunapaola/Documents/PYcodes/FLASK_BLEfirst/venv/lib/python3.14/site-packages/google/genai/errors.py", line 161, in raise_error
    raise ServerError(status_code, response_json, response)
google.genai.errors.ServerError: 503 UNAVAILABLE. {'error': {'code': 503, 'message': 'This model is currently experiencing high demand. Spikes in demand are usually temporary. Please try again later.', 'status': 'UNAVAILABLE'}}

