<template>
  <div v-if="!records || records.length === 0"> 
    <v-layout justify-center>
      <v-flex xs12 sm8 md6 >
        <v-alert  type= "warning" :value="true">В настоящий момент записи отсутствуют</v-alert>
      </v-flex>
    </v-layout>
  </div>
  
  <div v-else>
    <v-layout wrap class="search">
          <v-flex xs11 sm5 md4 lg3>
            <v-text-field
              v-model="search"
              label="Поиск"
              prepend-icon="search"
            ></v-text-field>
          </v-flex>
        </v-layout>
    <v-layout justify-center>
      
      <v-flex xs12 sm10 md6>
        
        
        <v-card  elevation="10" style="margin-bottom: 15px" v-for="record in carrentPage" :key="record.drive_file_url"> 
          <v-card-title style="font-size: 25px; padding-bottom: 0%" class="text-xs-center" >
            {{ record.event_name }}
          </v-card-title>
          <v-card-text  style="font-size: 14px; font-weight: 300; padding-top: 0%">
            {{ record.date }}
            {{ record.start_time }} - {{ record.end_time }}
          </v-card-text>

          <iframe class = "video" v-bind:src="record.drive_file_url" ></iframe>
          
        </v-card>
      </v-flex>
    </v-layout>
    <div class="text-xs-center">
    <v-pagination
      v-model="page"
      :length="pages"
    ></v-pagination>
  </div>
  </div>
</template>

<script>
import { mapState } from "vuex";
export default {
  data () {
      return {
        recordsPerPage: 5,
        page: 1,
        list: [],
        search: ""
      }
    },
  computed: mapState({
    records: state => state.records,
    pages(){
      return parseInt(this.records.length / this.recordsPerPage)+1
    },
    carrentPage(){
      let from = (this.page-1) * this.recordsPerPage
      let to = this.page * this.recordsPerPage
      return this.sortRecords.slice(from, to)
    },
    sortRecords(){
      return this.list = this.records.filter(item => {
        return item.event_name.includes(this.search) || item.date.includes(this.search)
      })
    }
  }),
};
</script>

<style>
.warning {
border-radius: 10px;
}
.video {
  width: 100%;
  height: 350px;
}
.search{
  margin-bottom: 30px;
}
</style>