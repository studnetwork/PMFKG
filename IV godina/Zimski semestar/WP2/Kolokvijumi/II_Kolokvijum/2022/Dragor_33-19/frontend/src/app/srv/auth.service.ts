import { Injectable } from '@angular/core';
import { api } from '../conf/api';
import { HttpClient, HttpResponse } from '@angular/common/http'
import { LoginModel, RegisterModel } from '../conf/models';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  constructor(
    private http: HttpClient
  ) { }

  login(body: LoginModel): Observable<HttpResponse<string>> {
    return this.http.post(
      `${api.host}/auth/login`, body, {responseType: 'text', observe: 'response'}
    )
  }

  register(body: RegisterModel): Observable<HttpResponse<string>> {
    return this.http.post(
      `${api.host}/auth/register`, body, {responseType: 'text', observe: 'response'}
    )
  }

}
