import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { ProfileComponent } from './ui/page/profile.component';
import { HomeComponent } from './ui/page/home.component';
import { LoginComponent } from './ui/page/login.component';
import { RegisterComponent } from './ui/page/register.component';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { JwtModule } from '@auth0/angular-jwt';
import { NavbarComponent } from './ui/comp/navbar.component';

import { api } from './conf/api';

@NgModule({
  declarations: [
    AppComponent,
    ProfileComponent,
    HomeComponent,
    LoginComponent,
    RegisterComponent,
    NavbarComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule,
    JwtModule.forRoot({
      config: { 
        tokenGetter: () => localStorage.getItem('jwt'),
        allowedDomains: [api.domain]
      }
    })
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
